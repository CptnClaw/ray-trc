#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include "ray.h"

// Interface for objects that may be hit by rays, such as spheres etc
class Hittable
{
    public:
        Hittable() = default;
        virtual ~Hittable() = default;

        // Check if ray hits the object at time tmin<=t<=tmax.
        virtual bool hit(const Ray &ray, double tmin, double tmax) = 0;

        // Calculates the normal of the object at the hit point.
        // Only call this function AFTER calling hit, and having checked that it returned true!
        // Otherwise it will return garbage. This is the caller's responsibility.
        virtual Vec3 calc_normal() = 0;

        double last_hit_t;
        
    protected:
        Ray last_hit_ray;
};

#endif // _HITTABLE_H_
