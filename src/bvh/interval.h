#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include "ray.h"

class Interval
{
    public:
        Interval(float start, float end); // Use to build finite volume intervals
        Interval(); // Default constructor is for empty intervals
        
        // Intersects this interval with another interval.
        // Returns true if the result is empty.
        bool intersect(const Interval &other);
        
        // Enlarges this interval to also encompass another interval (convex hull of union).
        void enlarge(const Interval &other);
        
        bool contains(float t) const;
        float length() const;
        float mid_point() const; // Do not call this function on an empty interval
        
        void make_empty(); // Turns this interval into an empty interval
        bool is_empty() const; // Checks if this interval is empty
        
        float start;
        float end;
};


#endif // _INTERVAL_H_
