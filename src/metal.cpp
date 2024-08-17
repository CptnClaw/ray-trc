#include "metal.h"

Metal::Metal(Color color)
{
    this->color = color;
}

bool Metal::scatter(const Ray& in, const Point hit_point, const Vec3 &normal, [[maybe_unused]] Random &randomizer,
                        Ray &out, Color &attenuation) const
{
    Vec3 projection = dot(in.direction(), normal) * normal;
    Vec3 out_dir = in.direction() - 2 * projection;
    out = Ray(hit_point, out_dir);
    attenuation = color;
    return true;
}