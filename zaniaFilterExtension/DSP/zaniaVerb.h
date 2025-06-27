//
//  zaniaVerb.h
//  zaniaFilter
//
//  Created by Colby Janecka on 6/26/25.
//

#include <vector>
#include <cmath>

class ZaniaVerb
{
private:
    
    double decay;
    size_t index, delay;
    std::vector<double> buffer;
    
public:
    
    // initializer
    ZaniaVerb(double decayFactor, size_t maxDelay);
    
    double processFrame(double frame);

    void setDecay(double factor);
    void setDelay(size_t time);
    
};
