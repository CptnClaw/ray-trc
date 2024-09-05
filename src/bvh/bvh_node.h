#ifndef _BVH_NODE_H_
#define _BVH_NODE_H_

#include <memory>
#include <vector>
#include "sphere.h"
#include "ray.h"

// When a node gets this number of spheres or less,
// do not create further nodes 
#define MAX_SPHERES_IN_LEAF 10

// Number of nodes in BVH are at most 2^BVH_MAX_DEPTH
#define BVH_MAX_DEPTH   8
#define BVH_TREE_SIZE   1 << BVH_MAX_DEPTH


// A node could be either internal (having other nodes as children) or a leaf (having spheres as children).
// Internal node:
//      first_child - Index of right child. Note that saving the index of the left child is redundant, since it is always +1 from its parent.
//      num_spheres - Always zero.
// Leaf:
//      first_child - Index of the first sphere associated to this leaf.
//      num_spheres - Number of spheres associated to this leaf, so the index of the last sphere is first_child+num_spheres-1 (inclusive).
class BVHNode
{
    public:
        AABB box;  // 24 bytes
        uint child_idx; 
        uint num_spheres;
};

class BVHTree
{
    public:
        BVHTree(const std::vector<shared_ptr<Sphere>> &objs);
        ~BVHTree();
        bool hit(const Ray &ray, double tmin, HitData &result) const;

    private:
        uint build_subtree(uint tree_depth, uint node_idx, uint first_sphere, uint num_spheres);

        BVHNode *nodes;
        uint size;
        std::vector<shared_ptr<Sphere>> spheres;
};

#endif // _BVH_NODE_H_
