#include "tracer.h"
#include "sphere.h"

Tracer::Tracer()
{
    objs.push_back(new Sphere(Point(0, 0, -2), 0.9));
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
    Sphere sphere(Point(0, 0, -2), 0.9);
    if (sphere.hit(ray, 0, 1000))
    {
        Color normal_color = sphere.calc_normal();
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