#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "random.h"
#include "bvh_node.h"

#define BVH_MAX_DEPTH   10

using std::shared_ptr;

class Tracer
{
    public:
        Tracer();
        Color calc_color(const Ray &ray, int max_depth);
    private:
        shared_ptr<BVHNode> bvh;
        Color sky_blue;
        
        void CreateMyScene();
        void CreateBookScene();
        void CreateBookFinalScene();
};

#endif // _TRACER_H_ 