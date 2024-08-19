#include "glass.h"
#include "vec3.h"

Glass::Glass(double material_refract_idx, double p) : p(p)
{
    color = Color(1.0, 1.0, 1.0);
    inward_refract_idx = 1.0 / material_refract_idx;
    outward_refract_idx = material_refract_idx;
}

Vec3 Glass::refract(const Vec3 &in_dir, const Vec3 normal, double refract_idx)
{
    Vec3 tangent = in_dir - std::fmax(dot(in_dir, normal), -1.0) * normal;
    Vec3 out_dir_tangent = refract_idx * tangent;
    Vec3 out_dir_normal = -std::sqrt(std::fabs(1 - out_dir_tangent.norm2())) * normal;
    return out_dir_tangent + out_dir_normal;
}

bool Glass::scatter(const Ray& in, const Point hit_point, const Vec3 &normal, [[maybe_unused]] Random &randomizer,
                        Ray &out, Color &attenuation) const
{ 
    double cur_refract_idx = inward_refract_idx;
    Vec3 cur_normal = normal;
    if (dot(in.direction(), normal) > 0) 
    {
        // Ray is going from inside to outside,
        // so effective refraction index has to be flipped (inversed),
        // and the normal has to point inward for the refraction calculations.
        cur_refract_idx = outward_refract_idx;
        cur_normal = -normal;
    }
    Vec3 refract_dir = Glass::refract(unit(in.direction()), cur_normal, cur_refract_idx);
    out = Ray(hit_point, refract_dir);
    attenuation = color;
    return p>0;
}