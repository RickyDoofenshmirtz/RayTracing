#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <cmath>

class sphere : public hittable
{
public:
    sphere(const point3& center, const double radius)
        : center(center), radius(std::fmax(0, radius))
    {
    }

    auto hit( //
        const ray& r,
        const double ray_tmin,
        const double ray_tmax,
        hit_record& rec) const -> bool override
    {
        const auto oc = center - r.origin();
        const auto a  = r.direction().length_squared();
        const auto h  = dot_product(r.direction(), oc);
        const auto c  = oc.length_squared() - (radius * radius);

        const auto d = (h * h) - (a * c);
        if (d < 0) { return false; }

        const auto squtd = std::sqrt(d);
        auto root        = (h - squtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
        {
            root = (h + squtd) / a;
            if (root <= ray_tmin || root >= ray_tmax) { return false; }
        }

        rec.t      = root;
        rec.p      = r[rec.t];
        rec.normal = (rec.p - center) / radius;

        return true;
    }

private:
    point3 center;
    double radius;
};