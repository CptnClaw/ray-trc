#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"
#include "random.h"

using std::shared_ptr;

enum DiffuseModel
{
    Uniform,
    Lambertian
};

class Tracer
{
    public:
        Tracer(DiffuseModel diffuse);
        Color calc_color(const Ray &ray, int max_depth);
    private:
        std::vector<shared_ptr<Hittable>> objs;
        Random rand;
        DiffuseModel diffuse;
};

#endif // _TRACER_H_ 