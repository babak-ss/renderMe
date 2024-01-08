#ifndef SPHERE
#define SPHERE
#include "hittable.h"
#include <cmath>
#include "vec3.h"

class sphere : public hittable {
public:    
    sphere() : center(point3(0, 0, -1)), radius(0.5) {}
    sphere(point3 center, double radius) : center(center), radius(radius) {}

    bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        vec3 oc = ray.origin() - center;
        double a = ray.direction().length_squared();
        double half_b = dot(oc, ray.direction());
        double c = oc.length_squared() - radius*radius;
        double discriminant = half_b*half_b - (a*c);
        if (discriminant < 0) return false;
        
        // Find the nearest root that lies in the acceptable range.
        double root =(- half_b - sqrt(discriminant)) / a;
        if (root > ray_tmax || root < ray_tmin) {
            root = (- half_b + sqrt(discriminant)) / a;
            if(root > ray_tmax || root < ray_tmin)
                return false;
        }

        rec.t = root;
        rec.p = ray.at(root);
        rec.n = (rec.p - center) / radius;
        
        return true;
    }

private:
    point3 center;
    double radius;
};
#endif