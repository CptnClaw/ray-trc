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