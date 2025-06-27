//
//  zaniaVerb.cpp
//  zaniaFilter
//
//  Created by Colby Janecka on 6/26/25.
//

#include "zaniaVerb.h" 
#include <cmath>

ZaniaVerb::ZaniaVerb(double decayFactor, size_t maxDelay)
    : decay(decayFactor)
    , delay(maxDelay)
    , index(0)
    , buffer(maxDelay, 0.0) {}

// Function that actually processes the reverb effect by frame.
double ZaniaVerb::processFrame(double frame){
    
    //get index of current buffer:
    size_t readIndex = (index + buffer.size() - delay) % buffer.size();
    
    double delayedFrame = buffer[readIndex];
    
    // add decay to delayed frame and combine with input
    double output = frame + delayedFrame * decay;
    
    // update current buffer slot with output frame
    buffer[index] = output;
    
    index = (index + 1) % buffer.size();
    
    return output;
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
    decay = factor;
}

void ZaniaVerb::setDelay(size_t time){
    delay = std::min(time, buffer.size());
}
