#include <limits>
#include "tracer.h"
#include "sphere.h"
#include "vec3.h"

const double MAX_T=std::numeric_limits<double>::infinity();
  
using std::make_shared;

Tracer::Tracer()
{
    objs.push_back(make_shared<Sphere>(Point(0, 0, -2), 0.9));
    objs.push_back(make_shared<Sphere>(Point(0.7, 0, -1.4), 0.3));
}

Color Tracer::calc_color(const Ray &ray)
{
    shared_ptr<Hittable> closest_obj = nullptr;
    double closest_t = MAX_T;
    for (shared_ptr<Hittable> obj : objs)
    {
        if (obj->hit(ray, 0, MAX_T) &&
            obj->last_hit_t < closest_t)
        {
            closest_t = obj->last_hit_t;
            closest_obj = obj;
        }
    }
    if (closest_obj != nullptr)
    {
        Vec3 normal = closest_obj->calc_normal();
        if (dot(normal, ray.direction()) <= 0)
        {
            // Ray is coming from outside the object
            Color normal_color = (normal + Vec3(1,1,1)) / 2; // Convert coords from [-1, 1] to [0, 1]
            return normal_color;
        }
        // Ray is coming from inside to object
        return Color(0, 0, 0);
    }

    // Not hit -- use background color
    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blue(0.1, 0.3, 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blend = (1-interp) * white + interp * blue; // Lerp
    return blend;
}