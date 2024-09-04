#include <iostream>
#include "interval.h"

Interval::Interval(float start, float end) 
{
    if (start < end)
    {
        this->start = start;
        this->end = end;
    }
    else
    {
        // Note this constructor is NOT for empty intervals, so flip coordinates if necessary
        this->start = end;
        this->end = start;
    }
}

Interval::Interval() 
{
    make_empty();
}

bool Interval::intersect(const Interval &other)
{
    // Check if either of the intervals are empty
    if (is_empty() || other.is_empty())
    {
        make_empty();
        return true;
    }
    
    // Both intervals are non-empty
    float max_start = std::max(start, other.start);
    float min_end = std::min(end, other.end);
    if (max_start <= min_end)
    {
        // There is a non-trivial intersection
        start = max_start;
        end = min_end;
        return false;
    }
    
    // Intersection is trivial
    make_empty();
    return true;
}

void Interval::enlarge(const Interval &other)
{
    // Verify that other is non-empty (otherwise there is nothing to do)
    if (!other.is_empty())
    {
        if (other.start < start || is_empty()) start = other.start;
        if (end < other.end || is_empty()) end = other.end;
    }
}

bool Interval::contains(float t) const
{
    return !is_empty() && start <= t && t <= end;
}

void Interval::make_empty() 
{
    // An interval is considered empty iff start > end.
    start = 1;
    end = 0;
}

bool Interval::is_empty() const
{
    // See function void make_empty()
    return start > end;
}

float Interval::length() const
{
    if (is_empty()) 
    {
        return 0;
    }
    return end - start;
}

float Interval::mid_point() const
{
    return (end + start) * 0.5;
}
