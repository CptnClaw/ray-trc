#include "sphere.h"

Sphere::Sphere(const Point &center, double radius)
{
    this->center = center;
    this->radius = radius;
}

bool Sphere::hit(const Ray &ray, double tmin, double tmax)
{
    // Quadratic data
    // TODO: There is an easy way to optimize the calculations below.
    //       Check if the code can be sped up.
    double a = ray.direction().norm2();
    double b = -2 * dot(ray.direction(), center - ray.origin());
    double c = (center - ray.origin()).norm2() - radius * radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        return false;
    }
    
    // Collision exists, now find its time and check if it falls in range
    double sqrt_discr = std::sqrt(discriminant);
    double hit_t = (-b - sqrt_discr) / (2*a);
    if (tmin <= hit_t && hit_t <= tmax)
    {
        this->last_hit_ray = ray;
        this->last_hit_t = hit_t;
        return true;
    }

    hit_t = (-b + sqrt_discr) / (2*a);
    if (tmin <= hit_t && hit_t <= tmax)
    {
        this->last_hit_ray = ray;
        this->last_hit_t = hit_t;
        return true;
    }
    
    return false;
}

Vec3 Sphere::calc_normal()
{
    Vec3 first_hit = last_hit_ray.at(last_hit_t) - center;
    return first_hit / radius;
}
    