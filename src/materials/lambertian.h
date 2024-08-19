#ifndef _LAMBERTIAN_H_
#define _LAMBERTIAN_H_

#include "material.h"

class Lambertian : public Material
{
    public:
        Lambertian(Color color);
        
        // Calculates a new scattered ray randomly according to Lambert's cosine law,
        // namely according to a distribution weighted mostly about the normal direction.
        // Always returns true since we are assuming now that diffusive materials never fully absorve light.
        bool scatter(const Ray& in, const Point hit_point, const Vec3 &normal, Random &randomizer,
                            Ray &out, Color &attenuation) const override;
        
};

#endif // _LAMBERTIAN_H_
