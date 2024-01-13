#include "camera.h"
#include "rtweekend.h"
#include "hittable.h"
#include "sphere.h"
#include "color.h"
#include "hittable_list.h"
#include <iostream>

color ray_color(const ray& ray, const hittable& world) {
    hit_record rec;
    if (world.hit(ray, interval(0, infinity), rec)) {
        return 0.5 * (rec.n + color(1, 1, 1));
    }
    
    vec3 unit_direction = unit_vector(ray.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
}

int main() {

    // World
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    camera camera;
    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 400;

    camera.render(world);
}