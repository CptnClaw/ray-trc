#ifndef _AABB_H_
#define _AABB_H_

#include "interval.h"
#include "ray.h"

// Axis-aligned bounding box
class AABB
{
    public:
        AABB() = default; // Empty box
        AABB(const Interval &xaxis, const Interval &yaxis, const Interval &zaxis);

        // Check if ray hits this box
        bool hit(const Ray &ray, double tmin, double tmax) const;

        // Enlarge this box so that it also contains other (convex hull of union)
        void enlarge(const AABB &other);
        
        // Return the axis (0, 1, or 2) whose side is the longest
        int longest_axis() const;
        float mid_point(int axis) const;
        
    private:
        Interval intervals[3];
};


#endif // _AABB_H_
