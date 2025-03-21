#pragma once

#include "vec3.hpp"

class ray
{
public:
    ray() = default;
    ray(const point3& origin, const vec3& direction)
        : m_origin(origin), m_direction(direction)
    {
    }

    [[nodiscard]] auto origin() const -> const point3& { return m_origin; }

    [[nodiscard]] auto direction() const -> const vec3& { return m_direction; }

    [[nodiscard]]
    auto at(double t) const -> point3
    {
        return m_origin + (t * m_direction);
    }

    auto operator[](double t) const -> point3
    {
        return m_origin + (t * m_direction);
    }

private:
    point3 m_origin;
    vec3 m_direction;
};