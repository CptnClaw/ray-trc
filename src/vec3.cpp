#include "vec3.h"

// Class methods
Vec3::Vec3() : values{0, 0, 0} {}
Vec3::Vec3(double x, double y, double z) : values{x, y, z} {}

double Vec3::norm() const
{
    return std::sqrt(norm2());
}

double Vec3::norm2() const
{
    return dot(*this, *this);
}

void Vec3::normalize()
{
    (*this) /= norm();
}

double Vec3::x() const    {return values[0];}
double Vec3::y() const    {return values[1];}
double Vec3::z() const    {return values[2];}
double Vec3::operator[](int i) const    {return values[i];}
double &Vec3::operator[](int i)         {return values[i];}

Vec3 Vec3::round() const
{
    return Vec3(double(int(values[0])),
                double(int(values[1])),
                double(int(values[2])));
}

void Vec3::clamp(double min, double max)
{
    values[0] = std::max(values[0], min);
    values[0] = std::min(values[0], max);
    values[1] = std::max(values[1], min);
    values[1] = std::min(values[1], max);
    values[2] = std::max(values[2], min);
    values[2] = std::min(values[2], max);
}

Vec3 Vec3::operator-() const
{
    return Vec3(-values[0], -values[1], -values[2]);
}

Vec3 &Vec3::operator+=(const Vec3 &w)
{
    values[0] += w[0];
    values[1] += w[1];
    values[2] += w[2];
    return *this;
}

Vec3 &Vec3::operator*=(double t)
{
    values[0] *= t;
    values[1] *= t;
    values[2] *= t;
    return *this;
}

Vec3 &Vec3::operator/=(double t)
{
    return (*this) *= (1/t);
}


// Utility functions
Vec3 operator+(const Vec3 &v, const Vec3 &w)
{
    return Vec3(v[0]+w[0], v[1]+w[1], v[2]+w[2]);
}

Vec3 operator-(const Vec3 &v, const Vec3 &w)
{
    return Vec3(v[0]-w[0], v[1]-w[1], v[2]-w[2]);
}

Vec3 operator/(const Vec3 &v, double t)
{
    return v*(1/t);
}

Vec3 operator*(const Vec3 &v, double t)
{
    return Vec3(v[0]*t, v[1]*t, v[2]*t);
}

Vec3 operator*(double t, const Vec3 &v)
{
    return v*t;
}

double dot(const Vec3 &v, const Vec3 &w)
{
    return v[0]*w[0] + v[1]*w[1] + v[2]*w[2];
}

Vec3 cross(const Vec3 &v, const Vec3 &w)
{
    return Vec3(v[1]*w[2] - v[2]*w[1],
                v[2]*w[0] - v[0]*w[2],
                v[0]*w[1] - v[1]*w[0]);
}

Vec3 unit(const Vec3 &v)
{
    Vec3 u(v[0], v[1], v[2]);
    u.normalize();
    return u;
}

std::ostream &operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v[0] << " " << v[1] << " " << v[2];
}