#include <iostream>
#include <limits>
#include "tracer.h"
#include "sphere.h"
#include "vec3.h"
#include "lambertian.h"
#include "metal.h"

const double MIN_T=0.001; // Avoid fake collisions at very low t that come from floating point rounding errors
const double MAX_T=std::numeric_limits<double>::infinity();
  
using std::make_shared;

Tracer::Tracer()
{
    // Ground
    shared_ptr<Material> grnd = make_shared<Lambertian>(Color(0.7, 0.7, 0.7));
    objs.push_back(make_shared<Sphere>(Point(0, -101, -2), 100, grnd));

    // Three spheres on top of each other
    double radius1 = 1;
    double radius2 = 0.25;
    double radius3 = 0.125;
    Point center1 = Point(-0.8, 0, -2);
    Point center2 = center1 + unit(Point(1, 1, 1)) * (radius1 + radius2);
    Point center3 = center2 + unit(Point(2, 1, 2)) * (radius2 + radius3);
    shared_ptr<Material> material1 = make_shared<Lambertian>(Color(0.7, 0.7, 0.7));
    shared_ptr<Material> material2 = make_shared<Metal>(Color(0.7, 0.7, 0.7), 0.15);
    shared_ptr<Material> material3 = make_shared<Lambertian>(Color(0.7, 0.7, 0.7));
    objs.push_back(make_shared<Sphere>(center1, radius1, material1));
    objs.push_back(make_shared<Sphere>(center2, radius2, material2));
    objs.push_back(make_shared<Sphere>(center3, radius3, material3));
    
    // Golden sphere on the side
    shared_ptr<Material> extra_material = make_shared<Metal>(Color(0.82, 0.5, 0.2), 0.02);
    objs.push_back(make_shared<Sphere>(Point(1.2, -1.2, -2.2), 0.8, extra_material));
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
        if (dot(closest_hit.normal, ray.direction()) > 0)
        {
            // Ray is hitting the object from the inside
            return Color(0, 0, 0);
        }
        
        Ray scattered;
        Color attenuation;
        if (!closest_hit.material->scatter(ray, closest_hit.hit_point, closest_hit.normal, rand, scattered, attenuation))
        {
            // Ray is totally absorbed
            return Color(0, 0, 0);
        }
        
        // Returned the color of scattered ray 
        return pointwise_prod(attenuation, calc_color(scattered, max_depth - 1));
    }

    // Not hit -- use background color
    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blue(0.1, 0.3, 1.0);
    Color white(1.0, 1.0, 1.0);
    Color blend = (1-interp) * white + interp * blue; // Lerp
    return blend;
}