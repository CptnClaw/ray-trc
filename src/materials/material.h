#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <memory>
#include "vec3.h"
#include "ray.h"

using std::shared_ptr;

enum class MaterialType
{
    Lambertian,
    Metal,
    Glass
};

class Material
{
    public:
        // Please do not call any constructor directly, but use factories instead.
        // Second constructor must remain public for std::make_shared to work in factories...
        Material() = delete; 
        Material(MaterialType type); 
        
        // Factories
        static shared_ptr<Material> CreateLambertian(Color color);
        static shared_ptr<Material> CreateMetal(Color color, double roughness);
        static shared_ptr<Material> CreateGlass(double material_refract_idx);

        // Calculates a new scattered ray its attenuation based on the specific material type.
        // Returns false if the ray was fully absorbed (i.e. no scattering).
        bool scatter(const Ray& in, const Point hit_point, const Vec3 &normal,
                            Ray &out, Color &attenuation) const;
        
    private:

        MaterialType type;
        Color color;
        
        // Metal properties
        double roughness;
        
        // Glass properties
        double inward_refract_idx;
        double outward_refract_idx;
        
        // Type-specific scatter implementations
        bool scatter_lambertian(const Point &hit_point, const Vec3 &normal, Ray &out) const;
        bool scatter_metal(const Ray& in, const Point &hit_point, const Vec3 &normal, Ray &out) const;
        bool scatter_glass(const Ray& in, const Point &hit_point, const Vec3 &normal, Ray &out) const;

        // Schlick's approximation to calculate the reflection coefficient of a glass material
        static double reflection_coeff(double refraction, double cosine_theta);
};


#endif // _MATERIAL_H_
