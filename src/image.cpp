#include <iostream>
#include "image.h"
#include "vec3.h"

#define MAX_COLOR 255

Color calc_color(Ray &ray)
{
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