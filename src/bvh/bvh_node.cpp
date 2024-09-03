#include "bvh_node.h"

BVHNode::BVHNode(const std::vector<shared_ptr<Sphere>> &objs, int max_depth)
{
    // Create bounding box containing all spheres
    for (shared_ptr<Sphere> s : objs)
    {
        box.enlarge(s->bounding());
    }

    // Check if leaf or internal node
    if (objs.size() <= MAX_SPHERES_IN_LEAF || max_depth == 0)
    {
        // This is a leaf
        spheres = objs;
        left = nullptr;
        right = nullptr;
    }
    else
    {
        // This is an internal node
        // Split spheres to two sets according to mid point of longest axis
        int axis = box.longest_axis();
        double mid_point = box.mid_point(axis);
        std::vector<shared_ptr<Sphere>> left_objs, right_objs;
        for (shared_ptr<Sphere> s : objs)
        {
            if (s->center[axis] < mid_point)
            {
                left_objs.push_back(s);
            }
            else
            {
                right_objs.push_back(s);
            }
        }
        left = new BVHNode(left_objs, max_depth-1);  // Send one half to left
        right = new BVHNode(right_objs, max_depth-1); // Send other half to right
    }
}

BVHNode::~BVHNode()
{
    if (left != nullptr) delete left;
    if (right != nullptr) delete right;
}

bool BVHNode::hit(const Ray &ray, double tmin, HitData &result) const
{
    if (!box.hit(ray, tmin, result.hit_time)) 
    {
        return false;
    }

    // If node has spheres, it is a leaf, so the recursion ends here
    if (!spheres.empty())
    {
        bool hit_found = false;
        for (shared_ptr<Sphere> s : spheres)
        {
            hit_found = s->hit(ray, tmin, result) || hit_found;
        }
        return hit_found;
    }

    // Node is not a leaf, keep recursing down the tree
    bool left_hit = left->hit(ray, tmin, result);
    bool right_hit = right->hit(ray, tmin, result);
    return left_hit || right_hit;
}