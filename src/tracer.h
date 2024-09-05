#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "random.h"
#include "bvh_node.h"
#include "viewport.h"

using std::shared_ptr;

class Tracer
{
    public:
        Tracer(BVHTree *bvh, Color sky_blue);
        void render(Viewport &view, int samples_per_pixel, int ray_bounce_limit, int tile_size);

    private:
        BVHTree *bvh;
        Color sky_blue;
        
        Color calc_color(const Ray &ray, int max_depth);
};

#endif // _TRACER_H_ 