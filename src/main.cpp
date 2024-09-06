#include <iostream>
#include <sstream>
#include "image.h"
#include "viewport.h"
#include "random.h"
#include "scene_factory.h"
#include "tracer.h"

#define PI              3.1415926535897932385
#define SCREEN_WIDTH    800
#define VFOV            (PI / 9)
#define ASPECT_RATIO    (4.0 / 3.0)

#define SAMPLES_PER_PIXEL 10
#define RAY_BOUNCE_LIMIT 20
#define TILE_SIZE 4

#define ROTATIONS 2

int main(int argc, char **argv)
{
    (void)argc; // Mark as unused
    (void)argv; // Mark as unused
    
    // Define camera position
    Point look_from(13, 2, 3);
    Point look_at;
    Vec3 vup(0, 1, 0);
    double lens_cone_angle = PI / 500.0;

    if (are_parallel(look_at - look_from, vup))
    {
        std::cerr << "view up must not be parallel to viewing direction" << std::endl;
        return 1;
    }

    // Initiaize scene and utilities
    Random::init();
    Color sky;
    BVHTree *world = SceneFactory::CreateBookFinalScene(sky);
    Tracer tracer(world, sky);
    Viewport view(SCREEN_WIDTH, ASPECT_RATIO, VFOV, look_from, look_at, vup, lens_cone_angle);
    bool result = true;

    // Loop over animation frames
    double rotation_cos = std::cos(2 * PI / ROTATIONS);
    double rotation_sin = std::sin(2 * PI / ROTATIONS);
    for (int i = 0; i < ROTATIONS; i++)
    {
        // Render frame 
        tracer.render(view, SAMPLES_PER_PIXEL, RAY_BOUNCE_LIMIT, TILE_SIZE);

        // Prepare output file and write frame
        std::stringstream filename;
        filename << "orot" << i << ".ppm";
        result = result && Image::drawPPM(filename.str(), view);

        // Rotate and get ready to draw next frame
        if (i+1 < ROTATIONS)
        {
            std::cout << ROTATIONS - i - 1 << " rotations remaining" << std::endl;
            view.rotate_camera(rotation_cos, rotation_sin);
        } 
    }
    delete world;
    return result ? 0 : 1;
}
