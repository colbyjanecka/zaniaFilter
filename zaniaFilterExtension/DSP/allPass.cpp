//
//  allPass.cpp
//  zaniaFilter
//
//  Created by Colby Janecka on 6/27/25.
//

#include "allPass.hpp"
#include <cmath>

// delayed all pass filter
AllPass::AllPass(size_t delay, double a)
    : delay(delay)
    , a(a)
    , index(0)
    , buffer(delay, 0.0) {}

double AllPass::process(double input){
    
    // get output from buffer
    double buffOut = buffer[index];
    
    double output = -a * input + buffOut;
    
    buffer[index] = input + buffOut * a;
    index = (index + 1) % buffer.size();
    
    return output;
}
