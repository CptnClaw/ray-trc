#include "viewport.h"

Viewport::Viewport(int screen_width, double vertical_fov,
                    Point look_from, Point look_at, Vec3 vup)
{
    // Set origin of rays and camera orthonormal system
    camera_center = look_from;
    focal_length = (look_at - look_from).norm();
    Vec3 viewing_direction = unit(look_at - look_from);
    v = unit(vup - dot(vup, viewing_direction) * viewing_direction);
    u = cross(viewing_direction, v);
    w = -viewing_direction;

    // Set widths and heights
    this->screen_width = screen_width;
    screen_height = int(screen_width / ASPECT_RATIO);
    screen_height = screen_height < 1 ? 1 : screen_height;
    double actual_aspect_ratio = double(screen_width) / double(screen_height);
    viewport_height = 2 * std::tan(vertical_fov / 2) * focal_length;
    viewport_width = viewport_height * actual_aspect_ratio;

    // Calculate viewport rect
    Point viewport_center = look_at;
    horizontal_vec = viewport_width * u;
    vertical_vec = -viewport_height * v;
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