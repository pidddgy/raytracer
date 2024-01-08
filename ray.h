#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
    public:
        ray() {} // empty constructor
        ray(const point3& origin, const vec3& direction): orig(origin), dir(direction) {} // member initializer list

        point3 origin() const {
            return orig;
        }

        vec3 direction() const {
            return dir;
        }

        vec3 at(double t) const {
            return orig + dir*t;
        }
    private:
        point3 orig;
        vec3 dir;
};

#endif