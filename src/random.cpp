#include <cstdlib>
#include "random.h"

Random::Random()
{
    std::random_device seeder;
    rng = std::mt19937(seeder());
    uniform_dist = std::uniform_real_distribution<double>(0.0, 1.0);
    normal_dist = std::normal_distribution<double>(0.0, 1.0);
}

double Random::gen_uniform()
{
    return uniform_dist(rng);
}

double Random::gen_uniform(double min_val, double max_val)
{
    return (gen_uniform() * (max_val - min_val)) + min_val;
}

Vec3 Random::gen_uniform_unit_vec()
{
    // Gaussians are spherically symmetrical, so their projection to the sphere distributes uniformly
    return unit(Vec3(normal_dist(rng), normal_dist(rng), normal_dist(rng)));
}