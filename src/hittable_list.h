#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class hittable_list : public hittable {
public:
    std::vector<shared_ptr <hittable> > objects;

    hittable_list() {}
    hittable_list(shared_ptr<hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& ray, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record tmp_rec;
        bool hit_anything = false;
        double distance_to_closest = ray_tmax;

        for (const auto& object : objects) { // TODO: wtf is this loop!?
            if (object->hit(ray, ray_tmin, distance_to_closest, tmp_rec)) {
                hit_anything = true;
                distance_to_closest = tmp_rec.t;
                rec = tmp_rec;
            }
        }

        return hit_anything;
    }
};
#endif