#pragma once

#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>

class vec3
{
public:
    using class_type = vec3;
    using value_type = double;

    vec3() = default;
    vec3(value_type e0, value_type e1, value_type e2)
        : m_data{ e0, e1, e2 }
    {
    }

    // auto x() -> value_type& { return e[0]; }
    [[nodiscard]] auto x() const -> const value_type& { return m_data[0]; }

    // auto y() -> value_type& { return e[1]; }
    [[nodiscard]] auto y() const -> const value_type& { return m_data[1]; }

    // auto z() -> value_type& { return e[2]; }
    [[nodiscard]] auto z() const -> const value_type& { return m_data[2]; }

    auto operator-() const -> class_type { return { -x(), -y(), -z() }; }

    auto operator[](std::size_t i) -> value_type& { return m_data[i]; }
    auto operator[](std::size_t i) const -> const value_type&
    {
        return m_data[i];
    }

    auto operator+=(const class_type& src) -> class_type&
    {
        for (std::size_t i{}; i < 3; ++i) { m_data[i] += src.m_data[i]; }
        return *this;
    }

    auto operator*=(value_type t) -> class_type&
    {
        for (auto& x : m_data) { x *= t; }
        return *this;
    }

    auto operator/=(value_type t) -> class_type& { return *this *= 1 / t; }

    [[nodiscard]]
    auto length_squared() const -> value_type
    {
        return (x() * x()) + (y() * y()) + (z() * z());
    }

    [[nodiscard]]
    auto length() const -> value_type
    {
        return std::sqrt(length_squared());
    }

private:
    std::array<value_type, 3> m_data{};
};

using point3 = vec3;

inline auto operator<<(std::ostream& out, const vec3& v) -> std::ostream&
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline auto operator+(const vec3& v1, const vec3& v2) -> vec3
{
    return { v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z() };
}

inline auto operator-(const vec3& v1, const vec3& v2) -> vec3
{
    return { v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z() };
}

inline auto operator*(const vec3& v1, const vec3& v2) -> vec3
{
    return { v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z() };
}

inline auto operator*(vec3::value_type t, const vec3& v) -> vec3
{
    return { t * v.x(), t * v.y(), t * v.z() };
}

inline auto operator*(const vec3& v, vec3::value_type t) -> vec3
{
    return t * v;
}

inline auto operator/(const vec3& v, vec3::value_type t) -> vec3
{
    return (1 / t) * v;
}

inline auto dot_product(const vec3& v1, const vec3& v2) -> vec3::value_type
{
    return (v1.x() * v2.x()) + (v1.y() + v2.y()) + (v1.z() + v2.z());
}

inline auto cross_product(const vec3& v1, const vec3& v2) -> vec3
{
    return { (v1.y() * v2.z()) - (v1.z() * v2.y()),
             (v1.z() * v2.x()) - (v1.x() * v2.z()),
             (v1.x() * v2.y()) - (v1.y() * v2.z()) };
}

inline auto unit_vector(const vec3& v) -> vec3 { return v / v.length(); }
