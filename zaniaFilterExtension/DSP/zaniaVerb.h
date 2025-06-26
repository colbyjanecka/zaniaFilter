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
    
    double decayFactor;
    int delayTime;
    std::vector<double> delayBuffer;
    
public:
    
    // initializer
    ZaniaVerb(double decayFactor, int delayTime);
    
    double processFrame(double frame);

    
};
