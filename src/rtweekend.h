#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <limits>
#include <memory>

// common headers
#include "interval.h"
#include "ray.h"
#include "vec3.h"

// usings
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// utility functions
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

#endif