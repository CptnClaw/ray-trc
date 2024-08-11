#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include <memory>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

using std::shared_ptr;

class Tracer
{
    public:
        Tracer();
        Color calc_color(const Ray &ray);
    private:
        std::vector<shared_ptr<Hittable>> objs;
};

#endif // _TRACER_H_ 