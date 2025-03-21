#pragma once

#include "vec3.hpp"
#include <ostream>

using color = vec3;

inline void write_color(std::ostream& out, const color& pixel_color)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto rbyte = static_cast<int>(255.999 * r);
    auto gbyte = static_cast<int>(255.999 * g);
    auto bbyte = static_cast<int>(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}