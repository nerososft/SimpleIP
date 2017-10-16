//
// Created by neroyang on 2017/10/14.
//

#include "Pixel.h"

namespace OpenIP {
    Pixel::Pixel(int x, int y, ColorRGB *color) : x(x), y(y), color(color) {
        this->rectangle = new Rectangle(0, 0, 0, 0, color->R(), color->G(), color->B());
    }

    void Pixel::normalize(int width, int height) {
        this->rectangle->setX(-1.0f + (2.0f / width) * this->x);
        this->rectangle->setY(-1.0f + (2.0f / height) * this->y);
        this->rectangle->setWidth((2.0f / width));
        this->rectangle->setHeight((2.0f / height));
    }

    void Pixel::render() {
        this->rectangle->draw();
    }

}
