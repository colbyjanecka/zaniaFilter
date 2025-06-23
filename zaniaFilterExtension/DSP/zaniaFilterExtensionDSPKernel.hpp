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

/*
 zaniaFilterExtensionDSPKernel
 As a non-ObjC class, this is safe to use from render thread.
 */
class zaniaFilterExtensionDSPKernel {
public:
    void initialize(int inputChannelCount, int outputChannelCount, double inSampleRate) {
        mSampleRate = inSampleRate;
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
                
                // Do your sample by sample dsp here...
                outputBuffers[channel][frameIndex] = inputBuffers[channel][frameIndex] * mGain/100 * panMap;
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
    double mGain = 25;
    double mAttack = 1.0;
    double mPan = 0;
    double mTemp = 0;
    bool mBypassed = false;
    AUAudioFrameCount mMaxFramesToRender = 1024;
};
