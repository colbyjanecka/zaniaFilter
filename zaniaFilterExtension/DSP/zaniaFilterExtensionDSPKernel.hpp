//
//  zaniaFilterExtensionDSPKernel.hpp
//  zaniaFilterExtension
//
//  Created by Colby Janecka on 6/22/25.
//

#pragma once

#import <AudioToolbox/AudioToolbox.h>
#import <algorithm>
#import <vector>
#import <span>
#include <math.h>

#import "zaniaFilterExtensionParameterAddresses.h"
#include "zaniaVerb.h"

/*
 zaniaFilterExtensionDSPKernel
 As a non-ObjC class, this is safe to use from render thread.
 */
class zaniaFilterExtensionDSPKernel {
public:
    void initialize(int inputChannelCount, int outputChannelCount, double inSampleRate) {
        mChannelCount = inputChannelCount;
        mSampleRate = inSampleRate;
        reverbs.clear();
        for (int i = 0; i < mChannelCount; ++i) {
            reverbs.emplace_back(.5, 22050);
        }
    }
    
    void deInitialize() {
    }
    
    // MARK: - Bypass
    bool isBypassed() {
        return mBypassed;
    }
    
    void setBypass(bool shouldBypass) {
        mBypassed = shouldBypass;
    }
    
    // MARK: - Parameter Getter / Setter
    void setParameter(AUParameterAddress address, AUValue value) {
        switch (address) {
            case zaniaFilterExtensionParameterAddress::gain:
                mGain = value;
                break;
            case zaniaFilterExtensionParameterAddress:: attack:
                mAttack = value;
                break;
            case zaniaFilterExtensionParameterAddress:: pan:
                mPan = value;
                break;
            case zaniaFilterExtensionParameterAddress:: temp:
                mTemp = value;
                break;
            case zaniaFilterExtensionParameterAddress:: cutoff:
                mCutoff = value;
                break;
            case zaniaFilterExtensionParameterAddress:: resonance:
                mResonance = value;
                break;
            case zaniaFilterExtensionParameterAddress:: delayTime:
                mDelayTime = value;
                for (auto& r : reverbs) r.setDelay(int(44.1*value));
                break;
            case zaniaFilterExtensionParameterAddress:: decay:
                mDecay = value;
                for (auto& r : reverbs) r.setDecay(value);
                break;
        }
    }
    
    AUValue getParameter(AUParameterAddress address) {
        // Return the goal. It is not thread safe to return the ramping value.
        
        switch (address) {
            case zaniaFilterExtensionParameterAddress::gain:
                return (AUValue)mGain;
            case zaniaFilterExtensionParameterAddress::attack:
                return (AUValue) mAttack;
            case zaniaFilterExtensionParameterAddress::pan:
                return (AUValue) mPan;
            case zaniaFilterExtensionParameterAddress::temp:
                return (AUValue) mTemp;
            case zaniaFilterExtensionParameterAddress::cutoff:
                return (AUValue) mCutoff;
            case zaniaFilterExtensionParameterAddress::resonance:
                return (AUValue) mResonance;
            case zaniaFilterExtensionParameterAddress::delayTime:
                return (AUValue) mDelayTime;
            case zaniaFilterExtensionParameterAddress::decay:
                return (AUValue) mDecay;
                
            default: return 0.f;
        }
    }
    
    // MARK: - Max Frames
    AUAudioFrameCount maximumFramesToRender() const {
        return mMaxFramesToRender;
    }
    
    void setMaximumFramesToRender(const AUAudioFrameCount &maxFrames) {
        mMaxFramesToRender = maxFrames;
    }
    
    // MARK: - Musical Context
    void setMusicalContextBlock(AUHostMusicalContextBlock contextBlock) {
        mMusicalContextBlock = contextBlock;
    }
    
    /**
     MARK: - Internal Process
     
     This function does the core siginal processing.
     Do your custom DSP here.
     */
    void process(std::span<float const*> inputBuffers, std::span<float *> outputBuffers, AUEventSampleTime bufferStartTime, AUAudioFrameCount frameCount) {
        /*
         Note: For an Audio Unit with 'n' input channels to 'n' output channels, remove the assert below and
         modify the check in [zaniaFilterExtensionAudioUnit allocateRenderResourcesAndReturnError]
         */
        assert(inputBuffers.size() == outputBuffers.size());
        
        if (mBypassed) {
            // Pass the samples through
            for (UInt32 channel = 0; channel < inputBuffers.size(); ++channel) {
                std::copy_n(inputBuffers[channel], frameCount, outputBuffers[channel]);
            }
            return;
        }
        
        // Use this to get Musical context info from the Plugin Host,
        // Replace nullptr with &memberVariable according to the AUHostMusicalContextBlock function signature
        /*
         if (mMusicalContextBlock) {
         mMusicalContextBlock(nullptr, 	// currentTempo
         nullptr, 	// timeSignatureNumerator
         nullptr, 	// timeSignatureDenominator
         nullptr, 	// currentBeatPosition
         nullptr, 	// sampleOffsetToNextBeat
         nullptr);	// currentMeasureDownbeatPosition
         }
         */
        
        // Perform per sample dsp on the incoming float in before assigning it to out
        for (UInt32 channel = 0; channel < inputBuffers.size(); ++channel) {
            for (UInt32 frameIndex = 0; frameIndex < frameCount; ++frameIndex) {
                
                // PAN Algorithm: dead center has both channels at -3dB
                double panMap = ((mPan + 50)/100*(M_PI/2));
                if(channel == 1){ panMap = sin(panMap);
                } else { panMap = cos(panMap); }
                
                // get current frame
                float currentFrame = inputBuffers[channel][frameIndex];
                
                // run reverb before low pass filter
                double postReverb = reverbs[channel].processFrame(currentFrame);
                
                //FIR Lowpass algorithm yn = axn-(1-a))xn-1
                float postFilter = mTemp*postReverb + (1-mTemp)*previousFrame[channel];  // add to previous frame and divide
                
                float outputFrame = postFilter * mGain/100 * panMap;
                
                // Do your sample by sample dsp here...
                outputBuffers[channel][frameIndex] = outputFrame;
                //outputBuffers[channel][frameIndex] = inputBuffers[channel][frameIndex] * mGain/100 * panMap;
                
                
                previousFrame[channel] = postFilter; // store previous value
            }
        }
    }
    
    void handleOneEvent(AUEventSampleTime now, AURenderEvent const *event) {
        switch (event->head.eventType) {
            case AURenderEventParameter: {
                handleParameterEvent(now, event->parameter);
                break;
            }
                
            default:
                break;
        }
    }
    
    void handleParameterEvent(AUEventSampleTime now, AUParameterEvent const& parameterEvent) {
        setParameter(parameterEvent.parameterAddress, parameterEvent.value);
    }
    
    // MARK: Member Variables
    AUHostMusicalContextBlock mMusicalContextBlock;
    
    double mSampleRate = 44100.0;
    int mChannelCount = 1;
    double mGain = 25;
    double mAttack = 1.0;
    double mPan = 0;
    double mTemp = 0.5;
    double mCutoff = 20000.0;
    double mResonance = 0.0;
    bool mBypassed = false;
    AUAudioFrameCount mMaxFramesToRender = 1024;
    
    float previousFrame[2];
    
private:
    
    double mDecay;
    int mDelayTime;
    std::vector<ZaniaVerb> reverbs;

};
