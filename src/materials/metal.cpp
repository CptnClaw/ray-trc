#include "metal.h"
#include "random.h"

Metal::Metal(Color color, double roughness) : roughness(roughness)
{
    this->color = color;
}

bool Metal::scatter(const Ray& in, const Point hit_point, const Vec3 &normal, 
                        Ray &out, Color &attenuation) const
{
    Vec3 projection = dot(in.direction(), normal) * normal;
    Vec3 out_dir = unit(in.direction() - 2 * projection);
    out_dir += (roughness * Random::gen_uniform_unit_vec());
    out = Ray(hit_point, out_dir);
    attenuation = color;
    return dot(out_dir, normal) > 0;
}