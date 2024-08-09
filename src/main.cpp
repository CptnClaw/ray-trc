#include <iostream>
#include <fstream>
#include "image.h"

int main(int argc, char **argv)
{
    std::ofstream outfile("orot.ppm");
    if (!outfile)
    {
        std::cerr << "Error: Cannot open file for writing" << std::endl;
        return 1;
    }
    draw_example(outfile);
    return 0;
}