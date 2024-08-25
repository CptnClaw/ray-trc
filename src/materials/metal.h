#ifndef _METAL_H_
#define _METAL_H_

#include "material.h"

class Metal : public Material
{
    public:
        // Roughness controls the fuzziness of the reflections. Increasing it makes the material less shiny. Should be between zero and one.
        Metal(Color color, double roughness);
        
        // Calculates a new scattered ray that is perfectly reflected.
        bool scatter(const Ray& in, const Point hit_point, const Vec3 &normal, 
                            Ray &out, Color &attenuation) const override;

    private:
        double roughness;

};


#endif // _METAL_H_
