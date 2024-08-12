#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{
    public:
        // Returns a random number in [0, 1)
        static double get_rand();

        // Returns a random number in [min_val, max_val)
        static double get_rand(double min_val, double max_val);
};

#endif // _RANDOM_H_
