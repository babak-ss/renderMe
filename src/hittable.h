#ifndef HITTABLE
#define HITTABLE
#include "ray.h"
#include "color.h"

class hittable {
public:

    virtual bool is_hit(const ray& ray) { return true; }
    virtual color get_color(const ray& ray) { return color(0, 0, 0); }
};
#endif