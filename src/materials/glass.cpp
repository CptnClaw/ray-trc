#include "glass.h"
#include "vec3.h"
#include "random.h" 

Glass::Glass(double material_refract_idx)
{
    color = Color(1.0, 1.0, 1.0);
    inward_refract_idx = 1.0 / material_refract_idx;
    outward_refract_idx = material_refract_idx;
}

double Glass::reflection_coeff(double refraction, double cosine_theta)
{
    // This calculation is based on Schlick's approximation
    double R_0 = (1 - refraction)*(1 - refraction) / ((1 + refraction)*(1 + refraction));
    double R_theta = R_0 + (1 - R_0) * std::pow(1 - cosine_theta, 5);
    return R_theta;
}

bool Glass::scatter(const Ray& in, const Point hit_point, const Vec3 &normal, 
                        Ray &out, Color &attenuation) const
{ 
    // Calculate properties related to surface orientation
    double eff_refract_idx = inward_refract_idx;
    Vec3 eff_normal = normal;
    if (dot(in.direction(), normal) > 0) 
    {
        // Ray is going from inside to outside,
        // so effective refraction index has to be flipped (inversed),
        // and the normal has to point inward.
        eff_refract_idx = outward_refract_idx;
        eff_normal = -normal;
    }

    // Calculate refracted ray
    Vec3 in_dir = unit(in.direction());
    double cosine_theta = dot(in_dir, eff_normal);
    Vec3 projection = cosine_theta * eff_normal;
    Vec3 tangent = in_dir - projection;
    Vec3 out_dir_tangent = eff_refract_idx * tangent;
    double tg_norm2 = out_dir_tangent.norm2();
    if (tg_norm2 > 1 ||  // Total internal reflection
        Glass::reflection_coeff(eff_refract_idx, -cosine_theta) > Random::gen_uniform()) // Ray randomly reflected
    {
        // Ray is reflected instead of refracted
        out = Ray(hit_point, in_dir - 2 * projection);
    }
    else 
    {
        // Finish calculating refracted ray
        double complement2 = 1 - tg_norm2;
        Vec3 out_dir_normal = -std::sqrt(complement2) * eff_normal;
        out = Ray(hit_point, out_dir_tangent + out_dir_normal);
    }

    attenuation = color;
    return true;
}