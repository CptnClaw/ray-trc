#ifndef RAY_H_
#define RAY_H_

#include "vec3.h"

class Ray
{
    public:
        Ray() = default; // Null ray, usually better to call the next constructor
        Ray(const Point &origin, const Vec3 &direction);
        
        const Point &origin() const;
        const Vec3 &direction() const;
        
        Vec3 at(double t) const;

    private:
        Point orig;
        Vec3 dir;
};

#endif // RAY_H_
