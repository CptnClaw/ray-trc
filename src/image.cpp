#include <assert.h>
#include <iostream>
#include "image.h"
#include "vec3.h"

#define MAX_COLOR 255

bool is_coliding_sphere(const Ray &ray, Vec3 &sphere_normal)
{
    // Defining the sphere geometry
    Point sphere_center(0, 0, -2);
    double sphere_radius = 0.9;
    
    // Quadratic data
    double a = ray.direction().norm2();
    double b = -2 * dot(ray.direction(), sphere_center - ray.origin());
    double c = (sphere_center - ray.origin()).norm2() - sphere_radius * sphere_radius;
    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
    {
        return false;
    }
    
    // Collision was found, now calculate normal of (first) hit point
    double hit_t = (-b - std::sqrt(discriminant)) / (2*a);
    assert(hit_t >= 0);
    Vec3 first_hit = ray.at(hit_t) - sphere_center;
    sphere_normal = first_hit / sphere_radius;
    return true;
}

Color calc_color(const Ray &ray)
{
    Vec3 sphere_normal;
    if (is_coliding_sphere(ray, sphere_normal))
    {
        Color normal_color = (sphere_normal + Vec3(1,1,1)) / 2; // Convert coords from [-1, 1] to [0, 1]
        return normal_color * MAX_COLOR;
    }
    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blue(0.1, 0.3, 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blend = (1-interp) * white + interp * blue; // Lerp
    return blend * MAX_COLOR;
}

void draw_example(std::ostream &out, const Viewport &view)
{
    // Write PPM header
    out << "P3" << std::endl;
    out << view.screen_width << " " << view.screen_height << std::endl;
    out << MAX_COLOR << std::endl;
    
    // Write pixels
    for (int y = 0; y < view.screen_height; y++)
    {
        // Print progress bar
        if (y % 10 == 0)
        {
            std::clog << (view.screen_height - y) << " scanlines remaining" << std::endl;
        }

        for (int x = 0; x < view.screen_width; x++)
        {
            Ray ray = view.get_ray(x, y);
            out << calc_color(ray).round() << std::endl;
        }
    }
    std::clog << "Done" << std::endl;
}