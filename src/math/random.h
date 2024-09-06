#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "xoshiro256plus.h"
#include "vec3.h"

class Random
{
    public:

        // Call this when the program starts
        inline static void init()
        {
            xoshiro_state[0] = splitmix64_next();
            xoshiro_state[1] = splitmix64_next();
            xoshiro_state[2] = splitmix64_next();
            xoshiro_state[3] = splitmix64_next();
        }

        // Returns a random number in U[0, 1)
        inline static double gen_uniform()
        {
            unsigned long long randint = next();
            double randdbl = (randint >> 11) * 0x1.0p-53;
            return randdbl;
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
