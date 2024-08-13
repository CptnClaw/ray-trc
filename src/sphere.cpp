#include "sphere.h"

Sphere::Sphere(const Point &center, double radius)
{
    this->center = center;
    this->radius = radius;
}

bool Sphere::hit(const Ray &ray, double tmin, double tmax, HitData &result)
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
    
    // Collision exists
    // Find its time and check if it falls in range
    double sqrt_discr = std::sqrt(discriminant);
    double hit_t = (-b - sqrt_discr) / (2*a);
    if (hit_t < tmin || tmax < hit_t)
    {
        hit_t = (-b + sqrt_discr) / (2*a);
        if (hit_t < tmin || tmax < hit_t)
        {
            return false;
        }
    }
    result.hitter = ray;
    result.hit_time = hit_t;
    result.hit_point = ray.at(hit_t);
    result.normal = (result.hit_point - center) / radius;
    return true;
}

    