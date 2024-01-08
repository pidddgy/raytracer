// 3D Vector Class

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream> 

using std::sqrt;

class vec3 {
    public:
        double e[3];
        vec3(double e0, double e1, double e2) {
            e[0] = e0;
            e[1] = e1;
            e[2] = e2; 
        }
        vec3() {
            e[0] = 0;
            e[1] = 0;
            e[2] = 0;
        }

        double x() const { return e[0]; }
        double y() const { return e[1]; }
        double z() const { return e[2]; }

        vec3& operator += (vec3 w) {
            e[0] += w.e[0];
            e[1] += w.e[1];
            e[2] += w.e[2];
            return *this;
        }

        vec3& operator *= (double t) {
            e[0] *= t;
            e[1] *= t;
            e[2] *= t;
            return *this;
        }

        vec3& operator /= (double t) {
            return (*this) *= 1/t;
        }

        double length () const {
            return sqrt(length_squared());
        }

        double length_squared() const {
            return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
        }
};

using point3 = vec3;

// vector utility functions:

// output stream
inline std::ostream& operator << (std::ostream& out, const vec3 &v) {
    return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// addition
inline vec3 operator + (const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
} 

// subtraction
inline vec3 operator - (const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// multiplication (multiply each element)
inline vec3 operator * (const vec3 &u, const vec3 &v) {
    return vec3(u.e[0]*v.e[0], u.e[1]*v.e[1], u.e[2]*v.e[2]);
}

// multiplication (scalar)
inline vec3 operator * (const vec3 &u, double t) {
    return vec3(t*u.e[0], t*u.e[1], t*u.e[2]);
}

// division of vector by a scalar
inline vec3 operator / (const vec3 &u, double t) {
    return u*(1.0/t);
}

// dot product
inline double dot_product (const vec3 &u, const vec3 &v) {
    return u.e[0]*v.e[0] + u.e[1]*v.e[1] + u.e[2]*v.e[2];
} 

// cross product
inline vec3 cross_product(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1]*v.e[2] - u.e[2]*v.e[1],
                u.e[2]*v.e[0] - u.e[0]*v.e[2],
                u.e[0]*v.e[1] - u.e[1]*v.e[0]);
}

// unit vector
inline vec3 unit_vector (const vec3 &u) {
    return u / u.length();
}


#endif