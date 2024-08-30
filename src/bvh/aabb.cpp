#include "aabb.h"

AABB::AABB(const Interval &xaxis, const Interval &yaxis, const Interval &zaxis)
{
    intervals[0] = xaxis;
    intervals[1] = yaxis;
    intervals[2] = zaxis;
}

bool AABB::hit(const Ray &ray, double tmin, double tmax) const
{
    Point origin = ray.origin();
    Vec3 direction = ray.direction();
    Interval hit_t(tmin, tmax);
    for (int axis=0; axis<3; axis++)
    {
        // Check if ray is degenarate
        if (std::fabs(direction[axis]) < EPSILON)
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
        if (hit_t.intersect(Interval(start_t, end_t)))
        {
            return false;
        }
    }
    
    // If got here, no intersection has become empty, so hit_t must be non-empty
    return true;
}

void AABB::enlarge(const AABB &other)
{
    for (int axis=0; axis<3; axis++)
    {
        intervals[axis].enlarge(other.intervals[axis]);
    }
}

int AABB::longest_axis() const
{
    double lengths[3] = {intervals[0].length(), intervals[1].length(), intervals[2].length()};
    if (lengths[0] > lengths[1] && lengths[0] > lengths[2])
    {
        return 0;
    }
    if (lengths[1] > lengths[0] && lengths[1] > lengths[2])
    {
        return 1;
    }
    return 2;
}

double AABB::mid_point(int axis) const
{
    return intervals[axis].mid_point();
}
