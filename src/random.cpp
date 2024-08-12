#include <cstdlib>
#include "random.h"

double Random::get_rand()
{
    double result;
    do
    {
        result = double(std::rand()) / RAND_MAX;
    } while (result >= 1);
    return result;
}

double Random::get_rand(double min_val, double max_val)
{
    return (Random::get_rand() * (max_val - min_val)) + min_val;
}