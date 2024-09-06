#include "aabb.h"

AABB::AABB(const Interval &xaxis, const Interval &yaxis, const Interval &zaxis)
{
    intervals[0] = xaxis;
    intervals[1] = yaxis;
    intervals[2] = zaxis;
}

bool AABB::hit(const Ray &ray, double tmin, double tmax) const
{
    // Prepare variables in cache
    Point origin = ray.origin();
    Vec3 direction_inv = ray.direction_inv();

    // Slab method: Intersect hitting times for all three axes
    Interval hit_t(tmin, tmax);
    for (int axis=0; axis<3; axis++)
    {
        // Prepare variables in cache
        Interval I = intervals[axis];
        double o = origin[axis];
        double dinv = direction_inv[axis];

        // Intersect entire hit interval with the hit interval of current axis
        double start_t = (I.start - o) * dinv;
        double end_t = (I.end - o) * dinv;
        if (hit_t.intersect(Interval(start_t, end_t)))
        {
            // Trivial intersection means ray misses AABB
            return false;
        }
    }
    
    // If got here, no intersection has been found empty, so hit_t must be non-empty
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

float AABB::mid_point(int axis) const
{
    return intervals[axis].mid_point();
}
