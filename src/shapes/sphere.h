#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitdata.h"

class Sphere 
{
    public:
        Sphere(const Point &center, double radius, shared_ptr<Material> material);

        // Check if ray hits the sphere at time tmin<=t<=tmax,
        // and if so, return true and update last argument.
        bool hit(const Ray &ray, double tmin, double tmax, HitData &result);

    private:
        Point center;
        double radius;
        shared_ptr<Material> material;
};


#endif // _SPHERE_H_
