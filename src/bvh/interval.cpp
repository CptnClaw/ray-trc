#include <iostream>
#include "interval.h"

Interval::Interval(double start, double end) : start(start), end(end), is_special(false)
{
    if (end < start)
    {
        is_special = true;
        type = Set::EMPTY;
    }
}
Interval::Interval(Set type) : is_special(true), type(type) {}

Interval::Interval() : is_special(true), type(Set::EMPTY) {}

Interval& Interval::operator&=(const Interval &J)
{
    // Check if either of the intervals are special
    if (J.is_special)
    {
        switch (J.type)
        {
        case Set::REAL_LINE: 
            break;
        case Set::EMPTY: 
            this->is_special = true;
            this->type = Set::EMPTY;
            break;
        default: 
            std::cerr << "Error: Invalid interval type" << std::endl; 
            break;
        }
        return *this;
    }
    if (this->is_special)
    {
        switch (this->type)
        {
        case Set::REAL_LINE: 
            this->is_special = false;
            this->start = J.start;
            this->end = J.end;
            break;
        case Set::EMPTY:
            break;
        default:
            std::cerr << "Error: Invalid interval type" << std::endl;
            break;
        }
        return *this;
    }
    
    // Both intervals are finite-volume
    double max_start = std::max(this->start, J.start);
    double min_end = std::min(this->end, J.end);
    if (max_start <= min_end)
    {
        this->start = max_start;
        this->end = min_end;
    }
    else
    {
        this->is_special = true;
        this->type = Set::EMPTY;
    }
    return *this;
}

Interval Interval::operator&(const Interval &J) const
{
    // Check if either of the intervals are special
    if (this->is_special)
    {
        switch (this->type)
        {
        case Set::REAL_LINE: return J;
        case Set::EMPTY: return Interval(Set::EMPTY);
        default: std::cerr << "Error: Invalid interval type" << std::endl; return J;
        }
    }
    if (J.is_special)
    {
        switch (J.type)
        {
        case Set::REAL_LINE: return *this;
        case Set::EMPTY: return Interval(Set::EMPTY);
        default: std::cerr << "Error: Invalid interval type" << std::endl; return J;
        }
    }
    
    // Both intervals are finite-volume
    double max_start = std::max(this->start, J.start);
    double min_end = std::min(this->end, J.end);
    return Interval(max_start, min_end);
}

Interval Interval::operator|(const Interval &J) const
{
    // Check if either of the intervals are special
    if (this->is_special)
    {
        switch (this->type)
        {
        case Set::REAL_LINE: return Interval(Set::REAL_LINE);
        case Set::EMPTY: return J;
        default: std::cerr << "Error: Invalid interval type" << std::endl; return J;
        }
    }
    if (J.is_special)
    {
        switch (J.type)
        {
        case Set::REAL_LINE: return Interval(Set::REAL_LINE);
        case Set::EMPTY: return *this;
        default: std::cerr << "Error: Invalid interval type" << std::endl; return J;
        }
    }
    
    // Both intervals are finite-volume
    double min_start = std::min(this->start, J.start);
    double max_end = std::max(this->end, J.end);
    return Interval(min_start, max_end);
}

Interval& Interval::operator|=(const Interval &J)
{
    // Check if either of the intervals are special
    if (J.is_special)
    {
        switch (J.type)
        {
        case Set::REAL_LINE: 
            this->is_special = true;
            this->type = Set::REAL_LINE;
            break;
        case Set::EMPTY: 
            break;
        default: 
            std::cerr << "Error: Invalid interval type" << std::endl;
            break;
        }
        return *this;
    }
    if (this->is_special)
    {
        switch (this->type)
        {
        case Set::REAL_LINE: 
            break;
        case Set::EMPTY: 
            this->is_special = false;
            this->start = J.start;
            this->end = J.end;
            break;
        default: 
            std::cerr << "Error: Invalid interval type" << std::endl;
            break;
        }
        return *this;
    }
    
    // Both intervals are finite-volume
    double min_start = std::min(this->start, J.start);
    double max_end = std::max(this->end, J.end);
    this->start = min_start;
    this->end = max_end;
    return *this;
}

bool Interval::contains(double t) const
{
    if (is_special)
    {
        switch (type)
        {
        case Set::REAL_LINE: return true;
        case Set::EMPTY: return false;
        default: std::cerr << "Error: Invalid interval type" << std::endl; return false;
        }
    }
    return start <= t && t <= end;
}

bool Interval::is_empty() const
{
    return !is_special || type != Set::EMPTY;
}

double Interval::length() const
{
    return end - start;
}