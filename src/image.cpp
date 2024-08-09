#include <iostream>
#include "image.h"
#include "vec3.h"

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
        // Print progress bar
        std::clog << (DISPLAY_HEIGHT - y) << " scanlines remaining" << std::endl;

        for (int x = 0; x < DISPLAY_WIDTH; x++)
        {
            double r = 0;
            double g = double(x) / (DISPLAY_WIDTH - 1);
            double b = double(y) / (DISPLAY_HEIGHT - 1);

            Color pixel(r,g,b);
            pixel *= MAX_COLOR;
            out << pixel << std::endl;
        }
    }
    std::clog << "Done" << std::endl;
}