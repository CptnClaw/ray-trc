#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_

#include "vec3.h"
#include "bvh_node.h"

class SceneFactory
{
    public:
        static BVHTree* CreateMyScene(Color &sky_blue);
        static BVHTree* CreateBookScene(Color &sky_blue);
        static BVHTree* CreateBookFinalScene(Color &sky_blue);
};


#endif // _SCENE_FACTORY_H_
