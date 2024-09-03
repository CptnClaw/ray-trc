#include <iostream>
#include <sstream>
#include "image.h"
#include "viewport.h"
#include "random.h"

#define PI              3.1415926535897932385
#define SCREEN_WIDTH    800
#define VFOV            (PI / 4)
#define ASPECT_RATIO    (4.0 / 3.0)

#define SAMPLES_PER_PIXEL 20
#define RAY_BOUNCE_LIMIT 10

#define ROTATIONS 1

// Rotate a point around a center in the XZ plane
Point rotate(const Point &p, const Point &center, double cosine, double sine)
{
    Vec3 dir = p - center;
    double x = dir.x();
    double y = dir.y();
    double z = dir.z();
    Vec3 rotated_dir(x*cosine + z*sine, y, -x*sine + z*cosine);
    return center + rotated_dir;
}

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused
    
    // Define camera position
    Point look_from(13, 2, 13);
    Point look_at;
    Vec3 vup(0, 1, 0);
    double lens_cone_angle = PI / 500.0;

    if (are_parallel(look_at - look_from, vup))
    {
        std::cerr << "view up must not be parallel to viewing direction" << std::endl;
        return 1;
    }

    Random::init();
    Tracer tracer;
    bool result = true;
    double rotation_cos = std::cos(2 * PI / ROTATIONS);
    double rotation_sin = std::sin(2 * PI / ROTATIONS);
    for (int i = 0; i < ROTATIONS; i++)
    {
        std::cout << ROTATIONS - i << " rotations remaining" << std::endl;
        std::stringstream filename;
        filename << "orot" << i << ".ppm";

        Viewport view(SCREEN_WIDTH, ASPECT_RATIO, VFOV, look_from, look_at, vup, lens_cone_angle);
        Image image(filename.str(), &tracer, &view);
        result &= image.render(SAMPLES_PER_PIXEL, RAY_BOUNCE_LIMIT);

        look_from = rotate(look_from, look_at, rotation_cos, rotation_sin);
    }
    return result ? 0 : 1;
}
