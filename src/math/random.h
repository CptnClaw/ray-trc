#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <random>
#include "vec3.h"

class Random
{
    public:
        
        Random();

        // Returns a random number in U[0, 1)
        double gen_uniform();

        // Returns a random number in U[min_val, max_val)
        double gen_uniform(double min_val, double max_val);

        // Returns a random number N(0, 0.5)
        double gen_normal();
        
        // Returns a random unit vector, drawn uniformly on the unit sphere
        Vec3 gen_uniform_unit_vec();
        
    private:
        std::minstd_rand0 rng;
        std::uniform_real_distribution<double> uniform_dist;
        std::normal_distribution<double> normal_dist;
};

#endif // _RANDOM_H_
