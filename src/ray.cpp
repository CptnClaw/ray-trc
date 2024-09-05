#include "ray.h"

Ray::Ray(const Point &origin, const Vec3 &direction) : orig(origin), dir(direction)
{
    dir_inv = Vec3(1.0 / dir[0], 1.0 / dir[1], 1.0 / dir[2]);
}

const Point &Ray::origin() const { return orig; }
const Vec3 &Ray::direction() const { return dir; }
const Vec3 &Ray::direction_inv() const { return dir_inv; }

Vec3 Ray::at(double t) const
{
    return orig + t * dir; 
}
