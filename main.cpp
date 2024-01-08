#include <iostream>
#include "color.h"
#include "vec3.h"

int main() {
    int image_height = 256;
    int image_width = 256;

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";
    for(int i = 0; i < image_height; i++) {
        std::clog << "\r Scanlines remaining: " << image_height - i << " " << std::flush;
        for(int j = 0; j < image_width; j++) {
            double r = double(i) / (image_height - 1);
            double g = double(j) / (image_width - 1);
            double b = 0;
            auto pixel = color(r, g, b);
            write_color(std::cout, pixel);
        }
    }    
    std::clog << "Done.\n";
}