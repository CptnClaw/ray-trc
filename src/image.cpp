#include <assert.h>
#include <iostream>
#include <fstream>
#include "image.h"
#include "vec3.h"
#include "sphere.h"
#include "random.h"

#define MAX_COLOR 255
#define GAMMA 2.2
        
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

bool Image::drawPPM(const std::string &filename, const Viewport &view)
{
    // Open file
    std::ofstream out(filename);
    if (!out)
    {
        std::cerr << "Error: Cannot open file for writing" << std::endl;
        return false;
    }

    // Write PPM header
    double height = view.screen_height;
    double width = view.screen_width;
    out << "P3" << std::endl;
    out << width << " " << height << std::endl;
    out << MAX_COLOR << std::endl;
    
    // Iterate over pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Draw pixel to file
            Color color = view.get_pixel(x, y);
            color = linear_to_gamma(color); // Gamma correction
            out << color * MAX_COLOR << std::endl;
        }
    }
    return true;
}
