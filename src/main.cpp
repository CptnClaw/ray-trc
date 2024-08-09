#include <iostream>
#include <fstream>
#include "image.h"

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
    draw_example(outfile);
    return 0;
}