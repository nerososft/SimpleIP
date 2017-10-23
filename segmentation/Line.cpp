//
// Created by neroyang on 2017/10/23.
//

#include "Line.h"

namespace OpenIP {
    OpenIP::Line::Line(float k, float b) : k(k), b(b) {}

    float Line::getK() const {
        return k;
    }

    void Line::setK(float k) {
        Line::k = k;
    }

    float Line::getB() const {
        return b;
    }

    void Line::setB(float b) {
        Line::b = b;
    }

    std::ostream &OpenIP::operator<<(std::ostream &os, const Line &line) {
        os << "k: " << line.k << " b: " << line.b;
        return os;
    }

}
