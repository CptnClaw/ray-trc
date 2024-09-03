#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitdata.h"
#include "aabb.h"

class Sphere 
{
    public:
        Sphere(const Point &center, double radius, shared_ptr<Material> material);

        // Check if ray hits the sphere at time tmin<=t<=result.hit_time,
        // and if so, return true and update result.
        bool hit(const Ray &ray, double tmin, HitData &result) const;

        // Calculates a bounding box
        AABB bounding() const;

        Point center;
        double radius;

    private:
        shared_ptr<Material> material;
        AABB box;
};


#endif // _SPHERE_H_
