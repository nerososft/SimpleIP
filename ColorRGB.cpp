//
// Created by neroyang on 2017/10/14.
//

#include "ColorRGB.h"
namespace OpenIP {
    ColorRGB::ColorRGB(unsigned int r, unsigned int g, unsigned int b) : r(r), g(g), b(b) {}

    bool ColorRGB::operator<(const ColorRGB &rhs) const {
        if (r < rhs.r)
            return true;
        if (rhs.r < r)
            return false;
        if (g < rhs.g)
            return true;
        if (rhs.g < g)
            return false;
        return b < rhs.b;
    }

    bool ColorRGB::operator>(const ColorRGB &rhs) const {
        return rhs < *this;
    }

    bool ColorRGB::operator<=(const ColorRGB &rhs) const {
        return !(rhs < *this);
    }

    bool ColorRGB::operator>=(const ColorRGB &rhs) const {
        return !(*this < rhs);
    }


    bool ColorRGB::operator==(const ColorRGB &rhs) const {
        return r == rhs.r &&
               g == rhs.g &&
               b == rhs.b;
    }

    bool ColorRGB::operator!=(const ColorRGB &rhs) const {
        return !(rhs == *this);
    }

    std::ostream &operator<<(std::ostream &os, const ColorRGB &rgb) {
        os << "r: " << rgb.r << " g: " << rgb.g << " b: " << rgb.b;
        return os;
    }
}

