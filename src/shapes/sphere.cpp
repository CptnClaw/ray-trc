#include <memory>
#include "sphere.h"
#include "material.h"

using std::shared_ptr;

Sphere::Sphere(const Point &center, double radius, shared_ptr<Material> material)
                : center(center), radius(radius), material(material) {}

bool Sphere::hit(const Ray &ray, double tmin, double tmax, HitData &result) const
{
    // Quadratic data
    double a = ray.direction().norm2();
    Vec3 origin_to_center = center - ray.origin();
    double h = dot(ray.direction(), origin_to_center); // b = -2h
    double c = origin_to_center.norm2() - radius * radius;
    double discriminant = h*h - a*c; // actually discriminant / 4
    if (discriminant < 0)
    {
        return false;
    }
    
    // Collision exists
    // Find its time and check if it falls in range
    double sqrt_discr = std::sqrt(discriminant);
    double hit_t = (h - sqrt_discr) / a;
    if (hit_t < tmin || tmax < hit_t)
    {
        hit_t = (h + sqrt_discr) / a;
        if (hit_t < tmin || tmax < hit_t)
        {
            return false;
        }
    }
    result.hitter = ray;
    result.hit_time = hit_t;
    result.hit_point = ray.at(hit_t);
    result.normal = (result.hit_point - center) / radius;
    result.material = material;
    return true;
}

AABB Sphere::bounding() const
{
    Interval spans[3];
    for (int axis=0; axis<3; axis++)
    {
        double c = center[axis];
        spans[axis] = Interval(c-radius, c+radius);
    }
    return AABB(spans[0], spans[1], spans[2]);
}
