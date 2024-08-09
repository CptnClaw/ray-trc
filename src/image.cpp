#include <iostream>
#include "image.h"

#define MAX_COLOR 255

void draw_example(std::ostream &out)
{
    // Write PPM header
    out << "P3" << std::endl;
    out << DISPLAY_WIDTH << " " << DISPLAY_HEIGHT << std::endl;
    out << MAX_COLOR << std::endl;
    
    // Write pixels
    for (int y = 0; y < DISPLAY_HEIGHT; y++)
    {
        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            double r = double(x) / (DISPLAY_WIDTH - 1);
            double g = double(y) / (DISPLAY_HEIGHT - 1);
            double b = 0;

            int ir = int(r * MAX_COLOR);
            int ig = int(g * MAX_COLOR);
            int ib = int(b * MAX_COLOR);
            
            out << ir << " ";
            out << ig << " ";
            out << ib << std::endl;
        }
    }
}