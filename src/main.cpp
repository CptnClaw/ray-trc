#include <iostream>
#include "image.h"
#include "viewport.h"

#define PI              3.1415926535897932385
#define SCREEN_WIDTH    800
#define VFOV            (PI / 6)

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused
    
    // Define camera position
    Point look_from(-2, 2, 1);
    Point look_at(0, 0, -1);
    Vec3 vup(0, 1, 0);

    if (are_parallel(look_at - look_from, vup))
    {
        std::cerr << "view up must not be parallel to viewing direction" << std::endl;
        return 1;
    }

    Tracer tracer;
    Viewport view(SCREEN_WIDTH, VFOV, look_from, look_at, vup);
    Image image("orot.ppm", &tracer, &view);

    bool result = image.render();
    return result ? 0 : 1;
}