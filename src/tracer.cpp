#include <iostream>
#include <limits>
#include "tracer.h"
#include "sphere.h"
#include "vec3.h"
#include "lambertian.h"
#include "metal.h"
#include "glass.h"

const double MIN_T=0.001; // Avoid fake collisions at very low t that come from floating point rounding errors
const double MAX_T=std::numeric_limits<double>::infinity();
const Color WHITE(1.0, 1.0, 1.0);
  
using std::make_shared;

Tracer::Tracer()
{
    CreateMyScene();
}

void Tracer::CreateMyScene()
{
    // Sky
    sky_blue = Color(0.1, 0.3, 1.0);

    // Ground
    shared_ptr<Material> grnd = make_shared<Lambertian>(Color(0.7, 0.7, 0.7));
    objs.push_back(make_shared<Sphere>(Point(0, -101, -2), 100, grnd));

    // Three spheres on top ofeach other
    double radius1 = 1;
    double radius2 = 0.25;
    double radius3 = 0.125;
    Point center1 = Point(-0.8, 0, -2);
    Point center2 = center1 + unit(Point(1, 1, 1)) * (radius1 + radius2);
    Point center3 = center2 + unit(Point(2, 1, 2)) * (radius2 + radius3);
    shared_ptr<Material> material1 = make_shared<Lambertian>(Color(0.8, 0.4, 0.2));
    shared_ptr<Material> material2 = make_shared<Metal>(Color(0.7, 0.7, 0.7), 0.15);
    shared_ptr<Material> material3 = make_shared<Lambertian>(Color(0.8, 0.4, 0.2));
    objs.push_back(make_shared<Sphere>(center1, radius1, material1));
    objs.push_back(make_shared<Sphere>(center2, radius2, material2));
    objs.push_back(make_shared<Sphere>(center3, radius3, material3));
    
    // Golden dome on the side
    shared_ptr<Material> gold = make_shared<Metal>(Color(0.82, 0.5, 0.2), 0.02);
    objs.push_back(make_shared<Sphere>(Point(1.2, -1.2, -2.2), 0.8, gold));

    // Glass bubble in front
    shared_ptr<Material> glass = make_shared<Glass>(1.5);
    shared_ptr<Material> bubble = make_shared<Glass>(1.0 / 1.5);
    objs.push_back(make_shared<Sphere>(Point(0, -0.5, -1), 0.25, glass));
    objs.push_back(make_shared<Sphere>(Point(0, -0.5, -1), 0.2, bubble));
}

void Tracer::CreateBookScene()
{
    sky_blue = Color(0.5, 0.7, 1.0);
    auto material_ground = make_shared<Lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<Lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left = make_shared<Glass>(1.50);
    auto material_bubble = make_shared<Glass>(1.0 / 1.50);
    auto material_right = make_shared<Metal>(Color(0.8, 0.6, 0.2), 1.0);
    objs.push_back(make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
    objs.push_back(make_shared<Sphere>(Point( 0.0,    0.0, -1.2),   0.5, material_center));
    objs.push_back(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
    objs.push_back(make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.4, material_bubble));
    objs.push_back(make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));
}

void Tracer::CreateBookFinalScene()
{
    auto ground_material = make_shared<Lambertian>(Color(0.5, 0.5, 0.5));
    objs.push_back(make_shared<Sphere>(Point(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = rand.gen_uniform();
            Point center(a + 0.9*rand.gen_uniform(), 0.2, b + 0.9*rand.gen_uniform());

            if ((center - Point(4, 0.2, 0)).norm() > 0.9) {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = pointwise_prod(Color(rand.gen_uniform(), rand.gen_uniform(), rand.gen_uniform()),
                                    Color(rand.gen_uniform(), rand.gen_uniform(), rand.gen_uniform()));
                    sphere_material = make_shared<Lambertian>(albedo);
                    objs.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Color(rand.gen_uniform(0.5, 1), rand.gen_uniform(0.5, 1), rand.gen_uniform(0.5, 1)); 
                    auto fuzz = rand.gen_uniform(0, 0.5);
                    sphere_material = make_shared<Metal>(albedo, fuzz);
                    objs.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<Glass>(1.5);
                    objs.push_back(make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<Glass>(1.5);
    objs.push_back(make_shared<Sphere>(Point(0, 1, 0), 1.0, material1));

    auto material2 = make_shared<Lambertian>(Color(0.4, 0.2, 0.1));
    objs.push_back(make_shared<Sphere>(Point(-4, 1, 0), 1.0, material2));

    auto material3 = make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0);
    objs.push_back(make_shared<Sphere>(Point(4, 1, 0), 1.0, material3));
}

Color Tracer::calc_color(const Ray &ray, int max_depth)
{
    if (max_depth > 0)
    {
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
    }

    // Not hit -- use background color
    Vec3 unit_dir = unit(ray.direction());
    double interp = (unit_dir.y() + 1.0) / 2; // Convert y from [-1, 1] to [0, 1]
    Color blend = (1-interp) * WHITE + interp * sky_blue; // Lerp
    return blend;
}