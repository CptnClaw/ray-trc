#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <memory>
#include "ray.h"
#include "material.h"

using std::shared_ptr;

class HitData
{
    public:
        Ray hitter;
        double hit_time;
        Point hit_point;
        Vec3 normal;
        shared_ptr<Material> material;
};

// Interface for objects that may be hit by rays, such as spheres etc
class Hittable
{
    public:
        Hittable() = default;
        virtual ~Hittable() = default;

        // Check if ray hits the object at time tmin<=t<=tmax.
        virtual bool hit(const Ray &ray, double tmin, double tmax, HitData &result) = 0;

    protected:
        shared_ptr<Material> material;
};


#endif // _HITTABLE_H_
