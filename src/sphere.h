#ifndef SPHERE
#define SPHERE
#include "hittable.h"
#include <cmath>
#include "vec3.h"

class sphere : public hittable {
public:
    point3 center;
    double radius;
    
    sphere() : center(point3(0, 0, -1)), radius(0.5) {}
    sphere(point3 center, double radius) : center(center), radius(radius) {}

    bool is_hit (const ray& ray) { return !(determinant(ray) < 0); }

    color get_color (const ray& ray) {
        double det = determinant(ray);
        vec3 normal = unit_vector(ray.at(det) - center);
        normal = (normal + vec3(1, 1, 1)) / 2.0;
        return color(normal);
    }

private:

    double determinant(const ray& ray) {
        // formula
        vec3 oc = ray.origin() - center;
        auto a = ray.direction().length_squared();
        auto half_b = dot(oc, ray.direction());
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = half_b*half_b - (a*c);
        if (discriminant < 0) {
            return -1.0;
        }
        else {
            return (-half_b - sqrt(discriminant)) / a;
        }
    }
};
#endif