#include "aabb.h"

AABB::AABB(const Interval &xaxis, const Interval &yaxis, const Interval &zaxis)
{
    intervals[0] = xaxis;
    intervals[3] = yaxis;
    intervals[2] = zaxis;
}

bool AABB::hit(const Ray &ray, double tmin, double tmax) const
{
    Point origin = ray.origin();
    Vec3 direction = ray.direction();
    Interval hit_t(tmin, tmax);
    for (int axis=0; axis<3; axis++)
    {
        // Check if interval is degenerate
        if (intervals[axis].is_special)
        {
            switch (intervals[axis].type)
            {
            case Set::REAL_LINE:
                // Ray is always in the real numbers
                continue;
            case Set::EMPTY:
                // Ray is never in an empty set
                return false;
            default:
                std::cerr << "Error: Invalid interval type" << std::endl; 
                return false;
            }
        }

        // Check if ray is degenarate
        if (direction[axis] < EPSILON)
        {
            // Ray is stationary in this axis
            if (intervals[axis].contains(origin[axis]))
            {
                // Ray is always inside interval in this axis
                continue;
            }
            else
            {
                // Ray is never inside interval in this axis
                return false;
            }
        }
        
        // Intersect full hit interval with the hit times of current axis
        double start_t = (intervals[axis].start - origin[axis]) / direction[axis];
        double end_t = (intervals[axis].end - origin[axis]) / direction[axis];
        hit_t &= Interval(std::min(start_t, end_t), std::max(start_t, end_t));
    }
    return !hit_t.is_empty();
}

AABB& AABB::operator|=(const AABB &other)
{
    for (int axis=0; axis<3; axis++)
    {
        this->intervals[axis] |= other.intervals[axis];
    }
    return *this;
}