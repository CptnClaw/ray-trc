#ifndef _AABB_H_
#define _AABB_H_

#include "interval.h"
#include "ray.h"

// Axis-aligned bounding box
class AABB
{
    public:
        AABB(const Interval &xaxis, const Interval &yaxis, const Interval &zaxis);

        // Check if ray hits this box
        bool hit(const Ray &ray, double tmin, double tmax) const;

        // Enlarge this box so that it also contains other
        AABB& operator|=(const AABB &other);
        
    private:
        Interval intervals[3];
};


#endif // _AABB_H_
