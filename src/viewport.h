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
        // screen_width is the width (in pixels) of the display window.
        // vertical_fov (field of view) is the angle (in radians) between the upper and lower edges of the viewport.
        Viewport(int screen_width, double vertical_fov,
                Point look_from, Point look_at, Vec3 vup);
        
        Ray get_ray(int x, int y) const;

        int screen_width;
        int screen_height;

    private:
        
        // Orthonormal basis of camera space. As conventional:
        // u points right.
        // v points up.
        // w points back.
        Vec3 u,v,w;

        double viewport_width;
        double viewport_height;
        
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
