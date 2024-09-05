#include "viewport.h"

Viewport::Viewport(int screen_width, double aspect_ratio, double vertical_fov,
                    Point look_from, Point look_at, Vec3 vup, double lens_cone_angle) : look_from(look_from), look_at(look_at), vup(vup)
{
    // Set some variables that remain constant under look_from rotations
    focal_length = (look_at - look_from).norm();
    lens_radius = std::tan(lens_cone_angle / 2.0) * focal_length;
    
    // Set widths and heights
    this->screen_width = screen_width;
    screen_height = int(screen_width / aspect_ratio);
    screen_height = screen_height < 1 ? 1 : screen_height;
    double actual_aspect_ratio = double(screen_width) / double(screen_height);
    viewport_height = 2 * std::tan(vertical_fov / 2.0) * focal_length;
    viewport_width = viewport_height * actual_aspect_ratio;
    
    // Set other variables that may change after look_from rotations
    update_look_from(look_from);
    
    // Create frame buffer
    target = new Color[screen_width * screen_height];
}

void Viewport::update_look_from(Point new_look_from)
{
    // Set origin of rays and camera orthonormal system
    camera_center = new_look_from;
    Vec3 viewing_direction = unit(look_at - new_look_from);
    v = unit(vup - dot(vup, viewing_direction) * viewing_direction);
    u = cross(viewing_direction, v);
    w = -viewing_direction;

    // Calculate viewport rect
    Point viewport_center = look_at;
    horizontal_vec = viewport_width * u;
    vertical_vec = -viewport_height * v;
    top_left = viewport_center - (horizontal_vec / 2) - (vertical_vec / 2);

    // Calculate pixel spacing and location
    horizontal_delta = horizontal_vec / screen_width;
    vertical_delta = vertical_vec / screen_height;
    first_pixel = Point(top_left + 0.5 * horizontal_delta + 0.5 * vertical_delta);

    // Calculate lens vectors
    lens_horizontal_vec = lens_radius * u;
    lens_vertical_vec = lens_radius * v;
}

Viewport::~Viewport()
{
    delete[] target;
}

void Viewport::rotate_camera(double cosine, double sine)
{
    // Apply rotation matrix
    Vec3 dir = look_from - look_at;
    double x = dir.x();
    double y = dir.y();
    double z = dir.z();
    update_look_from(look_at + Vec3(x*cosine + z*sine, y, -x*sine + z*cosine));
}

Ray Viewport::get_ray(int x, int y) 
{
    double lens_x = 0, lens_y = 0;
    if (lens_radius > 0)
    {
        do
        {
            lens_x = rand.gen_uniform(-1, 1);
            lens_y = rand.gen_uniform(-1, 1);
        } while (lens_x * lens_x + lens_y * lens_y > 1);
    }
    Point origin = camera_center + lens_x * lens_horizontal_vec + lens_y * lens_vertical_vec;
    Vec3 direction = first_pixel + (x * horizontal_delta) + (y * vertical_delta) - origin;
    return Ray(origin, direction);
}

void Viewport::set_pixel(int x, int y, Color color)
{
    color.clamp(0, 1);
    target[y * screen_width + x] = color;
}

Color Viewport::get_pixel(int x, int y) const
{
    return target[y * screen_width + x];
}
