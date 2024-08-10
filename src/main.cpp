#include <iostream>
#include <fstream>
#include "image.h"
#include "viewport.h"

#define SCREEN_WIDTH 400

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused

    std::ofstream outfile("orot.ppm");
    if (!outfile)
    {
        std::cerr << "Error: Cannot open file for writing" << std::endl;
        return 1;
    }
    Viewport view(SCREEN_WIDTH);
    draw_example(outfile, view);
    return 0;
}