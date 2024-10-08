#include <cstdlib>
#include <string.h>
#include <array>
#include <stack>
#include <algorithm>
#include "bvh_node.h"

#include <iostream>

bool compare_spheres_x(const shared_ptr<Sphere>& a, const shared_ptr<Sphere>& b)
{
    return a->center[0] < b->center[0];
}

bool compare_spheres_y(const shared_ptr<Sphere>& a, const shared_ptr<Sphere>& b)
{
    return a->center[1] < b->center[1];
}

bool compare_spheres_z(const shared_ptr<Sphere>& a, const shared_ptr<Sphere>& b)
{
    return a->center[2] < b->center[2];
}
bool (*compare_spheres[3])(const shared_ptr<Sphere> &, const shared_ptr<Sphere> &) = {compare_spheres_x, compare_spheres_y, compare_spheres_z};


BVHTree::BVHTree(const std::vector<shared_ptr<Sphere>> &objs) : spheres(objs) 
{
    // Allocate tree and build recursively
    nodes = new BVHNode[BVH_TREE_SIZE];
    uint last_node_idx = build_subtree(0, 0, 0, spheres.size());
    size = last_node_idx + 1;
    std::cout << "BVH Size: " << size << std::endl;
    
    // Copy sorted spheres to a nice cozy array, unpacking shared_ptr (for memory locality)
    int num_spheres = spheres.size();
    primitives = static_cast<Sphere*>(malloc(sizeof(Sphere) * num_spheres));
    for (int i = 0; i < num_spheres; i++)
    {
        memcpy(primitives+i, spheres[i].get(), sizeof(Sphere));
    }
}

BVHTree::~BVHTree()
{
    delete[] nodes;
}

uint BVHTree::build_subtree(uint tree_depth, uint node_idx, uint first_sphere, uint num_spheres)
{
    BVHNode &node = nodes[node_idx];

    // Calculate bounding box of current sphere range
    uint after_last_sphere = first_sphere + num_spheres;
    for (uint i = first_sphere; i < after_last_sphere; i++)
    {
        node.box.enlarge(spheres[i]->bounding());
    }

    // Check if node is leaf or internal node
    if (num_spheres <= MAX_SPHERES_IN_LEAF || tree_depth + 1 == BVH_MAX_DEPTH)
    {
        // This is a leaf
        node.child_idx = first_sphere;
        node.num_spheres = num_spheres;
        return node_idx;
    }
    else
    {
        // This is an internal node
        node.num_spheres = 0;

        // Split spheres to two sets and build chid nodes accordingly
        int axis;
        double threshold;
        choose_split(node, first_sphere, after_last_sphere, axis, threshold);
        auto begin_itr = std::begin(spheres) + first_sphere;
        auto end_itr = std::begin(spheres) + after_last_sphere;
        std::sort(begin_itr, end_itr, compare_spheres[axis]);
        uint num_left_spheres = uint(num_spheres * 0.5);
        for (uint i = first_sphere+1; i < after_last_sphere; i++)
        {
            double value = spheres[i]->center[axis];
            if (value >= threshold)
            {
                num_left_spheres = i - first_sphere;
                break;
            }
        }

        // Build left and right subtrees
        uint last_node = build_subtree(tree_depth + 1, node_idx + 1, first_sphere, num_left_spheres);
        node.child_idx = last_node + 1; // depth-first ordering
        return build_subtree(tree_depth + 1, node.child_idx, first_sphere + num_left_spheres, num_spheres - num_left_spheres);
    }
}

void BVHTree::choose_split(const BVHNode &node, uint first_sphere, uint after_last_sphere, int &axis, double &threshold)
{
    // Prepare looking for minimal sah cost
    bool found = false;
    double min_cost = std::numeric_limits<double>::infinity();
    
    // Scan all spheres (their centers are the threshold candidates) and all axes
    for (uint i = first_sphere; i < after_last_sphere; i++)
    {for (int cur_axis = 0; cur_axis < 3; cur_axis++)
        {
            double cur_threshold = spheres[i]->center[cur_axis];
            double cur_cost = calc_sah_cost(first_sphere, after_last_sphere, cur_axis, cur_threshold);
            if (0 < cur_cost && cur_cost < min_cost)
            {
                found = true;
                min_cost = cur_cost;
                axis = cur_axis;
                threshold = cur_threshold;
            }
        }
    }
    if (!found)
    {
        // In case process above did not produce any sensible split,
        // just default to longest axis and mid point
        axis = node.box.longest_axis();
        threshold = node.box.mid_point(axis);
    }
}

double BVHTree::calc_sah_cost(uint first_sphere, uint after_last_sphere, int axis, double threshold)
{
    // Calculate split based on given axis and threshold
    int num_spheres_left = 0;
    int num_spheres_right = 0;
    AABB box_left, box_right;
    for (uint i = first_sphere + 1; i < after_last_sphere; i++)
    {
        shared_ptr<Sphere> cur_sphere = spheres[i];
        double value = cur_sphere->center[axis];
        if (value < threshold)
        {
            // Put sphere in left box
            num_spheres_left++;
            box_left.enlarge(cur_sphere->bounding());
        }
        else
        {
            // Put sphere in right box
            num_spheres_right++;
            box_right.enlarge(cur_sphere->bounding());
        }
    }
    
    // SAH cost formula
    return num_spheres_left * box_left.surface_area() + num_spheres_right * box_right.surface_area();
}

bool BVHTree::hit(const Ray &ray, double tmin, HitData &result) const
{
    // Traverse flat tree iteratively using a stack.
    // Each task contains the index of a node to traverse.
    std::stack<uint> tasks;
    tasks.push(0);
    bool found_hit = false;
    while (!tasks.empty())
    {
        // Prepare task for processing current node
        uint cur_task = tasks.top();
        BVHNode node = nodes[cur_task];
        tasks.pop();

        // Check if ray hits bounding box of current node
        if (!node.box.hit(ray, tmin, result.hit_time))
        {
            continue;
        }

        if (node.num_spheres != 0)
        {
            // Node is a leaf, so it has spheres to check collision with, but no further child nodes to process
            for (uint i = node.child_idx; i < node.child_idx + node.num_spheres; i++)
            {
                found_hit = primitives[i].hit(ray, tmin, result) || found_hit;
            }
        }
        else
        {
            // Node is not a leaf, keep traversing down the tree
            tasks.push(cur_task + 1); // Left child node
            tasks.push(node.child_idx); // Right child node            
        }
    }
    return found_hit;
}
