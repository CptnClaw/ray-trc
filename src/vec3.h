#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>
#include <cmath>

class Vec3
{
    public:
        Vec3();
        Vec3(double x, double y, double z);
        
        double norm() const; // AKA length
        double norm2() const; // Norm squared
        void normalize(); // Divides this by norm 

        // Coordinate getters
        double x() const;
        double y() const;
        double z() const;
        double operator[](int i) const;
        double& operator[](int i);
        
        // Vector space operations (unary or acting on this)
        Vec3 operator-() const; // negate
        Vec3& operator+=(const Vec3 &w); // vector addition
        Vec3& operator*=(double t); // multiplication by scalar
        Vec3& operator/=(double t); // division by scalar

    private:
        double values[3];
};


// Vector space operations (binary)
Vec3 operator+(const Vec3 &v, const Vec3 &w);
Vec3 operator-(const Vec3 &v, const Vec3 &w);
Vec3 operator*(const Vec3 &v, double t);
Vec3 operator*(double t, const Vec3 &v);
double dot(const Vec3 &v, const Vec3 &w);
Vec3 cross(const Vec3 &v, const Vec3 &w);

// Serializer
std::ostream& operator<<(std::ostream &out, const Vec3 &v);

// Define nice aliases
using Point = Vec3;
using Color = Vec3;

#endif // _VEC3_H_
