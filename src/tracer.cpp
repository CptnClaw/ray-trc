#include <iostream>
#include <limits>
#include "tracer.h"
#include "sphere.h"
#include "vec3.h"

const double MIN_T=0.001; // Avoid fake collisions at very low t that come from floating point rounding errors
const double MAX_T=std::numeric_limits<double>::infinity();
const Color WHITE(1.0, 1.0, 1.0);
const double GAUSSIAN_SIGMA=0.25;

Tracer::Tracer(BVHTree *bvh, Color sky_blue) : bvh(bvh), sky_blue(sky_blue) {}

void Tracer::render(Viewport &view, int samples_per_pixel, int ray_bounce_limit, int tile_size)
{
    double *offsets = new double[samples_per_pixel * 2];

    // Iterate over tiles of (tile_size x tile_size) pixels
    for (int yout = 0; yout < view.screen_height / tile_size; yout++)
    {for (int xout = 0; xout < view.screen_width / tile_size; xout++)
        {
            // Iterate over pixels inside tile
            for (int yin = 0; yin < tile_size; yin++)
            {for (int xin = 0; xin < tile_size; xin++)
                {
                    // Calculate (x,y) coordinate in the image
                    int y = yout * tile_size + yin;
                    int x = xout * tile_size + xin;
                    
                    // Calculate color of pixel as average over subpixel samples
                    Color color; 
                    Random::box_muller(GAUSSIAN_SIGMA, &offsets, samples_per_pixel * 2); // Generate Gaussian offsets in bulk
                    for (int s = 0; s < samples_per_pixel; s++)
                    {
                        Ray ray = view.get_ray(x + offsets[2*s], y + offsets[2*s+1]);
                        Color cur_color = calc_color(ray, ray_bounce_limit);
                        color += cur_color;
                    }
                    color /= samples_per_pixel; // Average samples
                    view.set_pixel(x, y, color);
                }
            }
        }

        // Print progress bar
        if (yout % 25 == 0)
        {
            std::clog << (view.screen_height - yout * tile_size) << " scanlines remaining" << std::endl;
        }
    }
    std::clog << "Done rendering frame" << std::endl;
    delete[] offsets;
}

Color Tracer::calc_color(const Ray &ray, int max_depth)
{
    if (max_depth > 0)
    {
        HitData closest_hit;
        closest_hit.hit_time = MAX_T;
        if (bvh->hit(ray, MIN_T, closest_hit))
        {
            Ray scattered;
            Color attenuation;
            if (!closest_hit.material->scatter(ray, closest_hit.hit_point, closest_hit.normal, scattered, attenuation))
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
