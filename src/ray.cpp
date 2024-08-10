#include "ray.h"

Ray::Ray(const Point &origin, const Vec3 &direction) : orig(origin), dir(direction) {}

const Point &Ray::origin() const { return orig; }
const Vec3 &Ray::direction() const { return dir; }

Vec3 Ray::at(double t) const
{
    return orig + t * dir; 
}
