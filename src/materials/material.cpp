#include "material.h"
#include "random.h"

using std::make_shared;


Material::Material(MaterialType type) : type(type) {}


shared_ptr<Material> Material::CreateLambertian(Color color)
{
    shared_ptr<Material> result = make_shared<Material>(MaterialType::Lambertian);
    result->color = color;
    return result;
}

shared_ptr<Material> Material::CreateMetal(Color color, double roughness)
{
    shared_ptr<Material> result = make_shared<Material>(MaterialType::Metal);
    result->color = color;
    result->roughness = roughness;
    return result;
}

shared_ptr<Material> Material::CreateGlass(double material_refract_idx)
{
    shared_ptr<Material> result = make_shared<Material>(MaterialType::Glass);
    result->color = Color(1.0, 1.0, 1.0);
    result->inward_refract_idx = 1.0 / material_refract_idx;
    result->outward_refract_idx = material_refract_idx;
    return result;
}

bool Material::scatter(const Ray& in, const Point hit_point, const Vec3 &normal, 
                        Ray &out, Color &attenuation) const
{ 
    attenuation = color;
    switch (type)
    {
    case MaterialType::Lambertian:
        return scatter_lambertian(hit_point, normal, out);
        break;
    case MaterialType::Metal:
        return scatter_metal(in, hit_point, normal, out);
        break;
    case MaterialType::Glass:
        return scatter_glass(in, hit_point, normal, out);
        break;
    default:
        return false;
        break;
    }
}

bool Material::scatter_lambertian(const Point &hit_point, const Vec3 &normal, Ray &out) const
{
    // Distribution lies more heavily near the surface normal
    Vec3 random_dir = normal + Random::gen_uniform_unit_vec();
    
    // Handle edge case where the random vector points to negative normal
    if (random_dir.is_zero())
    {
        random_dir = normal;
    }
    
    out = Ray(hit_point, random_dir);
    return true;
}

bool Material::scatter_metal(const Ray &in, const Point &hit_point, const Vec3 &normal, Ray &out) const
{
    Vec3 projection = dot(in.direction(), normal) * normal;
    Vec3 out_dir = unit(in.direction() - 2 * projection);
    out_dir += (roughness * Random::gen_uniform_unit_vec());
    out = Ray(hit_point, out_dir);
    return dot(out_dir, normal) > 0;
}

bool Material::scatter_glass(const Ray &in, const Point &hit_point, const Vec3 &normal, Ray &out) const
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
        Material::reflection_coeff(eff_refract_idx, -cosine_theta) > Random::gen_uniform()) // Ray randomly reflected
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
    return true;
}

double Material::reflection_coeff(double refraction, double cosine_theta)
{
    // This calculation is based on Schlick's approximation
    double R_0 = (1 - refraction)*(1 - refraction) / ((1 + refraction)*(1 + refraction));
    double R_theta = R_0 + (1 - R_0) * std::pow(1 - cosine_theta, 5);
    return R_theta;
}