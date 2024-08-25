#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <cstdlib>
#include <ctime>
#include <limits>
#include "vec3.h"

class Random
{
    public:

        // Call this when the program starts
        inline static void init()
        {
            std::srand(std::time(0));
        }

        // Returns a random number in U[0, 1)
        inline static double gen_uniform()
        {
            return double(std::rand()) / RAND_MAX;
        }

        // Returns a random number in U[min_val, max_val)
        inline static double gen_uniform(double min_val, double max_val)
        {
            return (gen_uniform() * (max_val - min_val)) + min_val;
        }

        // Returns a random unit vector, drawn uniformly on the unit sphere
        static Vec3 gen_uniform_unit_vec();
};

#endif // _RANDOM_H_
