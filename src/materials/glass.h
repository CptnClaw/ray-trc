#ifndef _GLASS_H_
#define _GLASS_H_

#include "material.h"

class Glass : public Material
{
    public:
        // material_refract_idx is the refraction index of the material relative to the embedding space.
        // p is the probability that a hitting ray will be refracted.
        Glass(double material_refract_idx, double p);
        
        // Calculates a new scattered ray that is either reflected or refracted with probability p.
        bool scatter(const Ray& in, const Point hit_point, const Vec3 &normal, Random &randomizer,
                            Ray &out, Color &attenuation) const override;

    private:
        double inward_refract_idx;
        double outward_refract_idx;
        double p;

        static Vec3 refract(const Vec3 &in_dir, const Vec3 normal, double refract_idx);
};


#endif // _GLASS_H_
