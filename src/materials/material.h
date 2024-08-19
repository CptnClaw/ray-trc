#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "vec3.h"
#include "ray.h"
#include "random.h"

class Material
{
    public:
        Material() = default;
        virtual ~Material() = default;

        // Calculates a new scattered ray its attenuation based on any specific material impl.
        // Returns false if the ray was fully absorbed (i.e. no scattering).
        virtual bool scatter(const Ray& in, const Point hit_point, const Vec3 &normal, Random &randomizer,
                            Ray &out, Color &attenuation) const = 0;
        
    protected:
        Color color;
};


#endif // _MATERIAL_H_
