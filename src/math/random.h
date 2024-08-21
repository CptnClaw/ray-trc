#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include "vec3.h"

class Random
{
    public:
        
        Random();

        // Returns a random number in [0, 1)
        double gen_uniform();

        // Returns a random number in [min_val, max_val)
        double gen_uniform(double min_val, double max_val);
        
        // Returns a random unit vector
        Vec3 gen_uniform_unit_vec();
        
    private:
        std::mt19937 rng;
        std::uniform_real_distribution<double> uniform_dist;
        std::normal_distribution<double> normal_dist;
};

#endif // _RANDOM_H_
