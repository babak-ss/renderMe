#ifndef HITTABLE_H
#define HITTABLE_H
#include "rtweekend.h"

class hit_record {
public:
    point3 p;
    vec3 n;
    double t;
    bool is_front_face;
    void set_face_normal(const ray& ray, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.
        is_front_face = (dot(ray.direction(), outward_normal) < 0);
        n = is_front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    // virtual ~hittable() = default;
    virtual bool hit (const ray& ray, interval ray_t, hit_record& rec) const = 0;
};
#endif