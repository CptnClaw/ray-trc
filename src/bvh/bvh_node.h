#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include <memory>
#include <vector>
#include "sphere.h"
#include "ray.h"

// When a node gets this number of spheres or less,
// do not create further nodes 
#define MAX_SPHERES_IN_LEAF 4

class BVHNode
{
    public:
        BVHNode(const std::vector<shared_ptr<Sphere>> &objs, int max_depth);
        ~BVHNode();
        bool hit(const Ray &ray, double tmin, double tmax, HitData &result) const;
    private:
        AABB box;
        BVHNode *left;
        BVHNode *right;
        std::vector<shared_ptr<Sphere>> spheres;
};

#endif // _BVH_NODE_H_
