#pragma once

#include "ray.hpp"
#include "vec3.hpp"

struct hit_record
{
    point3 p;
    vec3 normal;
    double t{};
};

class hittable
{
public:
    hittable() noexcept                              = default;
    virtual ~hittable() noexcept                     = default;
    hittable(const hittable&)                        = default;
    hittable(hittable&&) noexcept                    = default;
    auto operator=(const hittable&) -> hittable&     = default;
    auto operator=(hittable&&) noexcept -> hittable& = default;

    virtual auto
    hit(const ray& r, double ray_trim, double ray_tmax, hit_record& res) const
        -> bool = 0;
};