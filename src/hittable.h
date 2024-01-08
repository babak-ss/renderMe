#ifndef HITTABLE_H
#define HITTABLE_H
#include "ray.h"
#include "color.h"

class hit_record {
public:
    point3 p;
    vec3 n;
    double t;
};

class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit (const ray& ray, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};
#endif