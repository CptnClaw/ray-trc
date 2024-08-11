#ifndef _TRACER_H_
#define _TRACER_H_

#include <vector>
#include "vec3.h"
#include "ray.h"
#include "hittable.h"

class Tracer
{
    public:
        Tracer();
        ~Tracer();
        Color calc_color(const Ray &ray);
    private:
        std::vector<Hittable*> objs;
};

#endif // _TRACER_H_ 