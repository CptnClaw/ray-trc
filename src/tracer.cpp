#include <iostream>
#include <limits>
#include "tracer.h"
#include "sphere.h"
#include "vec3.h"

const double MIN_T=0.001; // Avoid fake collisions at very low t that come from floating point rounding errors
const double MAX_T=std::numeric_limits<double>::infinity();
const double BOUNCE_ABSORPTION=0.60;
  
using std::make_shared;

Tracer::Tracer(DiffuseModel diffuse) : diffuse(diffuse)
{
    // Ground
    objs.push_back(make_shared<Sphere>(Point(0, -101, -2), 100));

    // Three spheres
    double radius1 = 1;
    double radius2 = 0.25;
    double radius3 = 0.125;
    Point center1 = Point(-0.8, 0, -2);
    Point center2 = center1 + unit(Point(1, 1, 1)) * (radius1 + radius2);
    Point center3 = center2 + unit(Point(2, 1, 2)) * (radius2 + radius3);
    objs.push_back(make_shared<Sphere>(center1, radius1));
    objs.push_back(make_shared<Sphere>(center2, radius2));
    objs.push_back(make_shared<Sphere>(center3, radius3));
}

Color Tracer::calc_color(const Ray &ray, int max_depth)
{
    if (max_depth <= 0)
    {
        return Color(0, 0, 0);
    }

    HitData closest_hit;
    closest_hit.hit_time = MAX_T;
    
    for (shared_ptr<Hittable> obj : objs)
    {
        HitData hd;
        if (obj->hit(ray, MIN_T, MAX_T, hd) &&
            hd.hit_time < closest_hit.hit_time)
        {
            closest_hit = hd;
        }
    }

    if (closest_hit.hit_time < MAX_T)
    {
        if (dot(closest_hit.normal, ray.direction()) <= 0)
        {
            // Ray is hitting the object from the outside
            Color normal_color(0, 0, 0);// = (closest_hit.normal + Vec3(1,1,1)) / 2; // Convert coords from [-1, 1] to [0, 1]
            
            // Random ray bounce
            Vec3 random_dir;
            if (diffuse == DiffuseModel::Uniform)
            {
                // Distribution is uniform on the hemisphere above the surface
                random_dir = rand.gen_uniform_unit_vec();
                if (dot(random_dir, closest_hit.normal) < 0)
                {
                    // Make sure random bounce goes outside of the object (and not inside)
                    random_dir = -random_dir;
                }
            }
            else if (diffuse == DiffuseModel::Lambertian)
            {
                // Distribution lies more heavily near the surface normal
                random_dir = closest_hit.normal + rand.gen_uniform_unit_vec();
            }
            else
            {
                std::cerr << "Invalid diffuse model" << std::endl;
                return Color(0, 0, 0);
            }

            Ray random_ray(closest_hit.hit_point, random_dir);
            Color bounce_color = calc_color(random_ray, max_depth-1);
            return normal_color + (1 - BOUNCE_ABSORPTION) * bounce_color;
        }
        // Ray is hitting the object from the inside
        return Color(0, 0, 0);
    }

    // Not hit -- use background color
    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blue(0.1, 0.3, 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blend = (1-interp) * white + interp * blue; // Lerp
    return blend;
}