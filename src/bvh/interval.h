#ifndef _INTERVAL_H_
#define _INTERVAL_H_

#include "ray.h"

enum class Set
{
    REAL_LINE, // Interval equals the whole set of real numbers, (-\infty, \infty).
    EMPTY // Interval is an empty set.
};

class Interval
{
    public:
        Interval(double start, double end); // Use to build finite volume intervals
        Interval(Set type); // Use to build infinite-volume or empty intervals
        Interval(); // Default constructor is for empty intervals
        
        // Calculates the largest interval contained in both (intersection)
        Interval operator&(const Interval &J) const;
        Interval& operator&=(const Interval &J);
        
        // Calculates the smallest interval containing both (convex hull of union)
        Interval operator|(const Interval &J) const; 
        Interval& operator|=(const Interval &J);
        
        bool contains(double t) const;
        bool is_empty() const;
        
        double start;
        double end;

        bool is_special; // True if interval equals one the types defined in the enum Set.
        Set type;
};


#endif // _INTERVAL_H_
