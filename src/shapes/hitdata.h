#ifndef _HITTABLE_H_
#define _HITTABLE_H_

#include <memory>
#include "ray.h"
#include "material.h"

using std::shared_ptr;

class HitData
{
    public:
        Ray hitter;
        double hit_time;
        Point hit_point;
        Vec3 normal;
        shared_ptr<Material> material;
};


#endif // _HITTABLE_H_
