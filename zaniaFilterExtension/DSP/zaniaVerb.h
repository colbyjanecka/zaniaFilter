//
//  zaniaVerb.h
//  zaniaFilter
//
//  Created by Colby Janecka on 6/26/25.
//

#include <vector>
#include <cmath>
#include "allPass.hpp"

class ZaniaVerb
{
private:
    
    double decay;
    double prevInput, prevOutput;
    size_t index, delay;
    std::vector<double> buffer;
    AllPass filter1, filter2, filter3;
    
public:
    
    // initializer
    ZaniaVerb(double decay, size_t maxDelay);
    
    double processFrame(double frame);

    void setDecay(double factor);
    void setDelay(size_t time);
    
};
