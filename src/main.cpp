#include "rtweekend.h"
#include "hittable.h"
#include "sphere.h"
#include "color.h"
#include "hittable_list.h"
#include <iostream>

color ray_color(const ray& ray, const hittable& world) {
    hit_record rec;
    if (world.hit(ray, 0, infinity, rec)) {
        return 0.5 * (rec.n + color(1, 1, 1));
    }
    
    vec3 unit_direction = unit_vector(ray.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // Calculate the image height, and ensure that it's at least 1.
    int image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    // Viewport widths less than one are ok since they are real valued.
    double viewport_height = 2.0;
    double viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

    double focal_length = 1.0;

    vec3 viewport_u = vec3(viewport_width, 0, 0);
    vec3 viewport_v = vec3(0, -viewport_height, 0);

    point3 delta_u = viewport_u / image_width;
    point3 delta_v = viewport_v / image_height;

    point3 camera_center = vec3(0, 0, 0);

    point3 viewport_upper_left_position = camera_center - vec3(0, 0, focal_length) -
                                            (viewport_u /2) -
                                            (viewport_v /2);

    point3 pixel00 = viewport_upper_left_position + (0.5 * (delta_u + delta_v));
    
    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // std::clog << viewport_upper_left_position << " --> " << pixel00 << std::endl; //&&&&&
    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
            point3 pixel_center = pixel00 + (i * delta_u) + (j * delta_v);

            // std::clog << i << ", " << j << " :: " << pixel_center << std::endl; //&&&&&

            ray r = ray(camera_center, pixel_center - camera_center);
            // auto pixel_color = color(0, 0, (pixel_position.y() + 1) / 2.0);
            color pixel_color = ray_color(r, world);
            write_color(std::cout, pixel_color);
            // std::clog << unit_vector(ray.direction()) << std::endl; //&&&&&
        }
    }
    std::clog << "\rDone. \n";

}