#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <iostream>

using color = vec3; // a color is just a 3d vector
void write_color(std::ostream &out, color pixel) {
    // take a value in [0, 1] and translate it to 0, 256
    out << static_cast<int> (256.00 * pixel.x()) << " "
        << static_cast<int> (256.00 * pixel.y()) << " "
        << static_cast<int> (256.00 * pixel.z()) << "\n";
}

#endif