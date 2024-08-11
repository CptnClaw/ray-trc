#include "tracer.h"
#include "sphere.h"

#define MAX_T 1000

Tracer::Tracer()
{
    objs.push_back(new Sphere(Point(0, 0, -2), 0.9));
    objs.push_back(new Sphere(Point(0.7, 0, -1.4), 0.3));
}

Tracer::~Tracer()
{
    for (Hittable *obj : objs)
    {
        free(obj);
    }
}

Color Tracer::calc_color(const Ray &ray)
{
    Hittable *closest_obj = NULL;
    double closest_t = MAX_T;
    for (Hittable *obj : objs)
    {
        if (obj->hit(ray, 0, MAX_T) &&
            obj->last_hit_t < closest_t)
        {
            closest_t = obj->last_hit_t;
            closest_obj = obj;
        }
    }
    if (closest_obj != NULL)
    {
        Color normal_color = closest_obj->calc_normal();
        normal_color = (normal_color + Vec3(1,1,1)) / 2; // Convert coords from [-1, 1] to [0, 1]
        return normal_color;
    }

    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blue(0.1, 0.3, 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blend = (1-interp) * white + interp * blue; // Lerp
    return blend;
}