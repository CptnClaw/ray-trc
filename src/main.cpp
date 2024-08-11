#include <iostream>
#include "image.h"
#include "viewport.h"

#define SCREEN_WIDTH 800

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused

    Tracer tracer;
    Viewport view(SCREEN_WIDTH);
    Image image("orot.ppm", &tracer, &view);
    bool result = image.render();
    return result ? 0 : 1;
}