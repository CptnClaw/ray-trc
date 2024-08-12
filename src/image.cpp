#include <assert.h>
#include <iostream>
#include <fstream>
#include "image.h"
#include "vec3.h"
#include "sphere.h"
#include "random.h"

#define MAX_COLOR 255

#define SAMPLES_PER_PIXEL 20

Image::Image(const std::string &filename, Tracer *tracer, Viewport *view) : 
        filename(filename), tracer(tracer), view(view), width(view->screen_width), height(view->screen_height) {}

bool Image::render() const
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
        if (y % 10 == 0)
        {
            std::clog << (height - y) << " scanlines remaining" << std::endl;
        }

        for (int x = 0; x < width; x++)
        {
            Color color; // Start with (0, 0, 0) and accumulate samples
            for (int s = 0; s < SAMPLES_PER_PIXEL; s++)
            {
                double offset_h = Random::get_rand(-0.5, 0.5);
                double offset_v = Random::get_rand(-0.5, 0.5);
                Ray ray = view->get_ray(x + offset_h, y + offset_v);
                color += tracer->calc_color(ray);
            }
            color /= SAMPLES_PER_PIXEL; // Average samples
            out << (color * MAX_COLOR).round() << std::endl;
        }
    }
    std::clog << "Done" << std::endl;
    return true;
}

