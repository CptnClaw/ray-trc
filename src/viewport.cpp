#include "viewport.h"

Viewport::Viewport(int screen_width)
{
    // Set widths and heights
    this->screen_width = screen_width;
    screen_height = int(screen_width / ASPECT_RATIO);
    screen_height = screen_height < 1 ? 1 : screen_height;
    double actual_aspect_ratio = double(screen_width) / double(screen_height);
    viewport_height = 2;
    viewport_width = viewport_height * actual_aspect_ratio;

    // Set origin of rays
    camera_center = Point(); 
    focal_length = 1;

    // Calculate viewport rect
    Point viewport_center = camera_center + Vec3(0, 0, -focal_length);
    horizontal_vec = Vec3(viewport_width, 0, 0);
    vertical_vec = Vec3(0, -viewport_height, 0);
    top_left = viewport_center - (horizontal_vec / 2) - (vertical_vec / 2);

    // Calculate pixel spacing and location
    horizontal_delta = horizontal_vec / screen_width;
    vertical_delta = vertical_vec / screen_height;
    first_pixel = Point(top_left + 0.5 * horizontal_delta + 0.5 * vertical_delta);
}

Ray Viewport::get_ray(int x, int y) const
{
    Vec3 direction = first_pixel + (x * horizontal_delta) + (y * vertical_delta) - camera_center;
    return Ray(camera_center, direction);
}