#include "random.h"

uint64_t xoshiro_state[4];

Vec3 Random::gen_uniform_unit_vec()
{
    // Rejection sampling was found to be the fastest
    while (true)
    {
        Vec3 in_box(gen_uniform(-1, 1), gen_uniform(-1, 1), gen_uniform(-1, 1));
        if (in_box.norm2() < 1)
        {
            return unit(in_box);
        }
    }
}

void Random::box_muller(double sigma, double **results, int size)
{
    // Implementation courtesy of Wikipedia
    constexpr double two_pi = 2.0 * M_PI;
    for (int i=0; i<size/2; i++)
    {
        // create two random numbers, make sure u1 is greater than zero
        double u1, u2;
        do
        {
            u1 = gen_uniform();
        } while (u1 == 0);
        u2 = gen_uniform();

        // compute z0 and z1
        auto mag = sigma * sqrt(-2.0 * log(u1));
        (*results)[2*i] = mag * cos(two_pi * u2);
        (*results)[2*i+1] = mag * sin(two_pi * u2);
    }
}
