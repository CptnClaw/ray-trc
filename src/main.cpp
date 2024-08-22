#include <iostream>
#include "image.h"
#include "viewport.h"

#define PI              3.1415926535897932385
#define SCREEN_WIDTH    800
#define VFOV            (PI / 9)
#define ASPECT_RATIO    (4.0 / 3.0)

#define SAMPLES_PER_PIXEL 5
#define RAY_BOUNCE_LIMIT 6

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused
    
    // Define camera position
    Point look_from(13, 2, 3);
    Point look_at = 0;
    Vec3 vup(0, 1, 0);
    double lens_cone_angle = PI / 500.0;

    if (are_parallel(look_at - look_from, vup))
    {
        std::cerr << "view up must not be parallel to viewing direction" << std::endl;
        return 1;
    }

    Tracer tracer;
    Viewport view(SCREEN_WIDTH, ASPECT_RATIO, VFOV, look_from, look_at, vup, lens_cone_angle);
    Image image("orot.ppm", &tracer, &view);

    bool result = image.render(SAMPLES_PER_PIXEL, RAY_BOUNCE_LIMIT);
    return result ? 0 : 1;
}