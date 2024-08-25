#include "lambertian.h"
#include "random.h"

Lambertian::Lambertian(Color color)
{
    this->color = color;
}

bool Lambertian::scatter([[maybe_unused]] const Ray& in, const Point hit_point, const Vec3 &normal,
                        Ray &out, Color &attenuation) const
{
    // Distribution lies more heavily near the surface normal
    Vec3 random_dir = normal + Random::gen_uniform_unit_vec();
    
    // Handle edge case where the random vector points to negative normal
    if (random_dir.is_zero())
    {
        random_dir = normal;
    }
    
    out = Ray(hit_point, random_dir);
    attenuation = color;
    return true;
}