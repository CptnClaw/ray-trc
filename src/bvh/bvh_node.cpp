#include "bvh_node.h"

BVHNode::BVHNode(std::vector<shared_ptr<Sphere>> objs)
{
    for (shared_ptr<Sphere> s : objs)
    {
        box |= s->bounding();
    }
    int axis = box.longest_axis();
    // TODO: Divide axis
    left = new BVHNode(objs);  // Send one half to left
    right = new BVHNode(objs);  // Send other half to right
}

bool BVHNode::hit(const Ray &ray, double tmin, double tmax, HitData &result) const
{
    if (!box.hit(ray, tmin, tmax)) 
    {
        return false;
    }

    // If node has spheres, it is a leaf, so the recursion ends here
    if (!spheres.empty())
    {
        result.hit_time = tmax;
        for (shared_ptr<Sphere> s : spheres)
        {
            HitData hd;
            if (s->hit(ray, tmin, result.hit_time, hd))
            {
                result = hd;
            }
        }
        return result.hit_time < tmax;
    }

    // Node is not a leaf, keep recursing down the tree
    HitData left_data, right_data;
    bool left_hit = left->hit(ray, tmin, tmax, left_data);
    double new_tmax = left_hit ? left_data.hit_time : tmax;
    bool right_hit = right->hit(ray, tmin, new_tmax, right_data);
    if (!left_hit && !right_hit)
    {
        return false;
    }
    if (left_hit && right_hit)
    {
        if (left_data.hit_time < right_data.hit_time)
        {
            result = left_data;
            return true;
        }
        result = right_data;
        return true;
    }
    if (left_hit)
    {
        result = left_data;
        return true;
    }
    result = right_data;
    return true;
}