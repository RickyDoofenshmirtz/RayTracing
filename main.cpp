#include "color.hpp"
#include "ray.hpp"
#include "vec3.hpp"

#include <cstring>
#include <iostream>

namespace {
    auto ray_color(const ray& r) -> color
    {
        const vec3 unit_direction = unit_vector(r.direction());
        const double a            = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
    }
}

auto main() -> int
{
    const double aspect_ratio = 16.0 / 9.0;
    const int image_width     = 400;

    const int temp_height  = static_cast<int>(image_width / aspect_ratio);
    const int image_height = (temp_height < 1) ? 1 : temp_height;

    const double focal_length    = 1.0;
    const double viewport_height = 2.0;
    const double viewport_width =
        viewport_height * (static_cast<double>(image_width) / image_height);
    const point3 camera_center = point3(0, 0, 0);

    const vec3 viewport_u = vec3(viewport_width, 0, 0);
    const vec3 viewport_v = vec3(0, -viewport_height, 0);

    const vec3 pixel_delta_u = viewport_u / image_width;
    const vec3 pixel_delta_v = viewport_v / image_height;

    const vec3 viewport_upper_left = camera_center - vec3(0, 0, focal_length) -
                                     viewport_u / 2 - viewport_v / 2;
    const vec3 pixel100_loc =
        viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j{}; j < image_height; ++j)
    {
        std::clog << "\rScanlines remaining: " << (image_height - j)
                  << std::flush;
        for (int i{}; i < image_width; ++i)
        {
            const vec3 pixel_center =
                pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            const ray r(camera_center, ray_direction);
            const color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }
    std::clog << "\rDone\n";

    return 0;
}