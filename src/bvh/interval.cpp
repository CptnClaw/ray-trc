#include <iostream>
#include "interval.h"

Interval::Interval(double start, double end) 
{
    is_empty = false;
    if (start < end)
    {
        this->start = start;
        this->end = end;
    }
    else
    {
        this->start = end;
        this->end = start;
    }
}

Interval::Interval() : is_empty(true) {}

bool Interval::intersect(const Interval &other)
{
    // Check if either of the intervals are empty
    if (is_empty || other.is_empty)
    {
        is_empty = true;
        return true;
    }
    
    // Both intervals are non-empty
    double max_start = std::max(start, other.start);
    double min_end = std::min(end, other.end);
    if (max_start <= min_end)
    {
        start = max_start;
        end = min_end;
        return false;
    }
    is_empty = true;
    return true;
}

void Interval::enlarge(const Interval &other)
{
    // Verify that other is non-empty (otherwise there is nothing to do)
    if (!other.is_empty)
    {
        if (is_empty)
        {
            // If this is empty, enlarge should just make it equal other
            is_empty = false;
            start = other.start;
            end = other.start;
        }
        
        // Both interval are non-empty
        start = std::min(start, other.start);
        end = std::max(end, other.end);
    }
}

bool Interval::contains(double t) const
{
    return !is_empty && start <= t && t <= end;
}

double Interval::length() const
{
    if (is_empty) 
    {
        return 0;
    }
    return end - start;
}

double Interval::mid_point() const
{
    return (end + start) / 2;
}