//
//  allPass.hpp
//  zaniaFilter
//
//  Created by Colby Janecka on 6/27/25.
//

#include <cmath>
#include <vector>

class AllPass
{
private:
    size_t delay, index;
    double prevInput, prevOutput, a;
    std::vector<double> buffer;
    
public:
    AllPass(size_t delay, double a);
    double process(double input);
};
