#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "ray.h"

class HitData
{
    public:
        Ray hitter;
        double hit_time;
        Point hit_point;
        Vec3 normal;
};

// Interface for objects that may be hit by rays, such as spheres etc
class Hittable
{
    public:
        Hittable() = default;
        virtual ~Hittable() = default;

        // Check if ray hits the object at time tmin<=t<=tmax.
        virtual bool hit(const Ray &ray, double tmin, double tmax, HitData &result) = 0;
};


#endif // _HITTABLE_H_
