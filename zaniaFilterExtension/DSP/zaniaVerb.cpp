//
//  zaniaVerb.cpp
//  zaniaFilter
//
//  Created by Colby Janecka on 6/26/25.
//

#include "zaniaVerb.h" 
#include <cmath>

ZaniaVerb::ZaniaVerb(double decayFactor, int delayTime)
    : decayFactor(decayFactor)
    , delayTime(delayTime)
{
    // initialize buffer
    delayBuffer.resize(delayTime, 0.0);
}

// Function that actually processes the reverb effect by frame.
double ZaniaVerb::processFrame(double frame){
    
    // add new frame to delay buffer
    delayBuffer.push_back(frame);
    
    // decay buffer values by decayFactor
    for (int i = 0; i < delayBuffer.size(); ++i){
        delayBuffer[i] *= decayFactor;
    }
    
    // sum buffer to get output frame
    double output = 0.0;
    for (int i = 0; i < delayBuffer.size(); ++i){
        output += delayBuffer[i];
    }
    
    // remove last sample of buffer
    delayBuffer.erase(delayBuffer.begin());
    
    return output;
}
