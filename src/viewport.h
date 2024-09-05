#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include "vec3.h"
#include "ray.h"
#include "random.h"

// This viewport uses "right-handed coordinates",
// namely, y-axis goes up, x-axis goes right,
// and the negative z-axix goes in the viewing direction.
class Viewport
{
    public:
        // screen_width is the width (in pixels) of the display window.
        // vertical_fov (field of view) is the angle (in radians) between the upper and lower edges of the viewport.
        Viewport(int screen_width, double aspect_ratio, double vertical_fov,
                Point look_from, Point look_at, Vec3 vup, double lense_cone_angle);
        ~Viewport();
        
        Ray get_ray(int x, int y);
        void set_pixel(int x, int y, Color color);
        Color get_pixel(int x, int y) const;

        // Rotate look_from point around look_at point by a specific angle
        void rotate_camera(double cosine, double sine);

        int screen_width;
        int screen_height;

    private:
        // This function updates variables common to constructor and to rotate_camera
        void update_look_from(Point new_look_from);

        // Orthonormal basis of camera space. As conventional:
        // u points right.
        // v points up.
        // w points back.
        Vec3 u, v, w;

        double viewport_width;
        double viewport_height;
        
        // (Re)initialization parameters
        Point look_from, look_at;
        Vec3 vup;
        
        // Origin of rays
        Point camera_center;
        double focal_length;

        // Viewpoint rectangle in space
        Point top_left;
        Vec3 horizontal_vec;
        Vec3 vertical_vec;
        
        // Lens
        double lens_radius;
        Vec3 lens_horizontal_vec;
        Vec3 lens_vertical_vec;
        Random rand;
        
        // Distance between pixels
        Vec3 horizontal_delta; 
        Vec3 vertical_delta;
        
        // Location of center of top left pixel 
        Point first_pixel;
        
        // Frame buffer
        Color *target;
};


#endif // VIEWPORT_H_
