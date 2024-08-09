#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "vec3.h"
#include "ray.h"

#define ASPECT_RATIO (4.0/3.0)

// This viewport uses "right-handed coordinates",
// namely, y-axis goes up, x-axis goes right,
// and the negative z-axix goes in the viewing direction.
class Viewport
{
    public:
        Viewport(int screen_width);
        
        Ray get_ray(int x, int y) const;

        int screen_width;
        int screen_height;

    private:
        int viewport_width;
        int viewport_height;
        
        // Origin of rays
        Point camera_center;
        double focal_length;

        // Viewpoint rectangle in space
        Point top_left;
        Vec3 horizontal_vec;
        Vec3 vertical_vec;
        
        // Distance between pixels
        Vec3 horizontal_delta; 
        Vec3 vertical_delta;
        
        // Location of center of top left pixel 
        Point first_pixel;
};


#endif // VIEWPORT_H_
