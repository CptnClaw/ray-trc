#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hittable.h"

class Sphere : public Hittable
{
    public:
        Sphere(const Point &center, double radius);

        // Check if ray hits the sphere at time tmin<=t<=tmax.
        bool hit(const Ray &ray, double tmin, double tmax) override;

        // Calculates the normal of the sphere at the hit point.
        // Only call this function AFTER calling hit, and having checked that it returned true!
        // Otherwise it will return garbage. This is the caller's responsibility.
        Vec3 calc_normal() override;
    
    private:
        Point center;
        double radius;
};


#endif // _SPHERE_H_
