#include <assert.h>
#include <iostream>
#include <fstream>
#include "image.h"
#include "vec3.h"
#include "sphere.h"
#include "random.h"

#define MAX_COLOR 255
#define GAMMA 2.2

Image::Image(const std::string &filename, Tracer *tracer, Viewport *view) : 
        filename(filename), tracer(tracer), view(view), width(view->screen_width), height(view->screen_height) {}
        
// Gamma correction
inline Color linear_to_gamma(Color linear_color)
{
    Color gamma_color;
    for (int i=0; i<3; i++)
    {
        gamma_color[i] = std::pow(linear_color[i], 1.0 / GAMMA);
    }
    return gamma_color;
}

bool Image::render(int samples_per_pixel, int ray_bounce_limit)
{
    // Open file
    std::ofstream out(filename);
    if (!out)
    {
        std::cerr << "Error: Cannot open file for writing" << std::endl;
        return false;
    }
    
    // Write PPM header
    out << "P3" << std::endl;
    out << width << " " << height << std::endl;
    out << MAX_COLOR << std::endl;
    
    // Write pixels
    for (int y = 0; y < height; y++)
    {
        // Print progress bar
        if (y % 100 == 0)
        {
            std::clog << (height - y) << " scanlines remaining" << std::endl;
        }

        for (int x = 0; x < width; x++)
        {
            Color color; // Start with (0, 0, 0) and accumulate samples
            for (int s = 0; s < samples_per_pixel; s++)
            {
                double offset_h = Random::gen_uniform(-0.5, 0.5);
                double offset_v = Random::gen_uniform(-0.5, 0.5);
                Ray ray = view->get_ray(x + offset_h, y + offset_v);
                Color cur_color = tracer->calc_color(ray, ray_bounce_limit);
                color += cur_color;
            }
            color /= samples_per_pixel; // Average samples
            color.clamp(0, 1);
            color = linear_to_gamma(color); // Gamma correction
            out << color * MAX_COLOR << std::endl;
        }
    }
    std::clog << "Done" << std::endl;
    return true;
}

