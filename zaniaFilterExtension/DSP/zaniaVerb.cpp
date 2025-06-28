//
//  zaniaVerb.cpp
//  zaniaFilter
//
//  Created by Colby Janecka on 6/26/25.
//

#include "zaniaVerb.h" 
#include <cmath>

ZaniaVerb::ZaniaVerb(double decay, size_t maxDelay)
    : decay(decay)
    , delay(maxDelay)
    , prevInput(0.0), prevOutput(0.0)
    , index(0)
    , buffer(maxDelay, 0.0)
    , filter1(113, 0.65)
    , filter2(127, 0.7)
    , filter3(149, 0.6)
    {}


// Function that actually processes the reverb effect by frame.
double ZaniaVerb::processFrame(double frame){
    
    //get index of current buffer:
    size_t readIndex = (index + buffer.size() - delay) % buffer.size();
    
    double delayedFrame = buffer[readIndex];
    
    // Simple one-pole low pass filter
    const double alpha = 0.15; // Adjust 0.1–0.5 to taste
    prevOutput = alpha * delayedFrame + (1.0 - alpha) * prevOutput;
    
    // add decay to delayed frame and combine with input
    double output = frame + prevOutput * decay;

    // update current buffer slot with output frame
    buffer[index] = output;
    
    index = (index + 1) % buffer.size();
    
    double pass1 = filter1.process(output);
    double pass2 = filter2.process(pass1);
    double pass3 = filter3.process(pass2);
    
    return pass3;
}

/** c++
class SimpleReverb {
public:
    SimpleReverb(size_t maxDelay, double decay)
        : buffer(maxDelay, 0.0), decay(decay), index(0), delay(maxDelay) {}

    double process(double input) {
        size_t readIndex = (index + buffer.size() - delay) % buffer.size();
        double delayed = buffer[readIndex];
        double output = input + delayed * decay;
        buffer[index] = output;
        index = (index + 1) % buffer.size();
        return output;
    }

    void setDelay(size_t d) { delay = std::min(d, buffer.size()); }
    void setDecay(double d) { decay = d; }

private:
    std::vector<double> buffer;
    size_t index, delay;
    double decay;
};
**/

void ZaniaVerb::setDecay(double factor){
    decay = std::clamp(factor, 0.01, 0.90);
}

void ZaniaVerb::setDelay(size_t time){
    delay = std::clamp(time, size_t(1), buffer.size());
}
