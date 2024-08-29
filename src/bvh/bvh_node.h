#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include <memory>
#include <vector>
#include "sphere.h"
#include "ray.h"

class BVHNode
{
    public:
        BVHNode(std::vector<shared_ptr<Sphere>> objs);
        bool hit(const Ray &ray, double tmin, double tmax, HitData &result) const;
    private:
        AABB box;
        BVHNode *left;
        BVHNode *right;
        std::vector<shared_ptr<Sphere>> spheres;
};

#endif // _BVH_NODE_H_
