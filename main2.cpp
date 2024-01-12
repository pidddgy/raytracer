#include <iostream>
#include <algorithm>
#include "color.h"
#include "vec3.h"
#include "ray.h"

auto hit_sphere(const point3& center, const double radius,const ray& r) {
    auto oc = r.origin()-center;
    auto a = dot_product(r.direction(), r.direction());
    auto b = 2*dot_product(r.direction(), oc);
    auto c = dot_product(oc, oc) - radius*radius;
    auto discriminant = b*b - 4*a*c;
    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-b-sqrt(discriminant))/(2.0*a);
    }
}

color ray_color(const ray& r) {
    auto sphere_center = point3(-1, 0.5, -2);
    auto t = hit_sphere(sphere_center, 0.8, r);
    if(t > 0.0) {
        vec3 N = unit_vector(r.at(t) - sphere_center);
        return color(N.x()+1, N.y()+1, N.z()+1)*0.5;
    }

    // if(hit_sphere(point3(0.5, 0, -1), 0.2, r)) {
    //     return color(1, 0, 0);
    // }
    
    
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return color(1.0, 1.0, 1.0)*(1.0-a) + color(0.5, 0.7, 1.0)*a;
}
 
int main() {
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // calculate image height
    // https://stackoverflow.com/questions/103512/why-use-static-casttx-instead-of-tx
    int image_height = std::max(1, static_cast<int>(image_width / aspect_ratio));

    // arbitrarily we are going to decide viewport height is equal to 2
    // width/height might not be exactly the same as aspect ratio
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (static_cast<double> (image_width) / image_height);

    // the camera is an arbitrary point in 3d space
    // the distance from camera to viewport is 1.0 for now
    // the vector from camera to viewport center is orthagonal to the viewport
    auto focal_length = 1.0;
    auto camera_center = point3(0, 0, 0);

    // get the vectors from top left corner of the viewport to the top right and bottom left
    auto viewport_u = vec3(viewport_width, 0, 0);
    auto viewport_v = vec3(0, -viewport_height, 0);

    // calculate delta vectors for each pixel (scalar values)
    auto pixel_delta_u = viewport_u / image_width;
    auto pixel_delta_v = viewport_v / image_height;

    // right handed coordinate, x axis goes to right, y axis goes up, negative z axis goes in viewing direction
    // get locations of the upper left corner of the viewport
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;

    // recall: the viewport is padded by pixel_delta/2 so that each pixel is the center of its square
    auto pixel00_loc = viewport_upper_left = viewport_upper_left + pixel_delta_u/2 + pixel_delta_v/2;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int j = 0; j < image_height; j++) {
        std::clog << "\r Scanlines remaining: " << image_height - j << " " << std::flush;
        for(int i = 0; i < image_width; i++) {
            auto pixel_center = pixel00_loc + (pixel_delta_u*i) + (pixel_delta_v*j);
            auto ray_direction = pixel_center - camera_center;

            ray r(camera_center, ray_direction);
            const auto c = ray_color(r);
            write_color(std::cout, c);
        }
    }    
    std::clog << "Done.\n";
}