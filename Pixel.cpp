//
// Created by neroyang on 2017/10/14.
//

#include "Pixel.h"

namespace OpenIP {
    Pixel::Pixel(int x, int y, std::shared_ptr<ColorRGB> color) : x(x), y(y), color(color) {
        isTransperent = false;
        this->rectangle = std::make_shared<Rectangle>(0, 0, 0, 0, color->R(), color->G(), color->B());
    }

    void Pixel::normalize(int width, int height) {
        this->rectangle->setX(-1.0f + (2.0f / width) * this->x);
        this->rectangle->setY(1.0f - (2.0f / height) * this->y);
        this->rectangle->setWidth((2.0f / width));
        this->rectangle->setHeight((2.0f / height));
    }

    void Pixel::render() {
        this->rectangle->draw();
    }

    int Pixel::getX() const {
        return x;
    }

    void Pixel::setX(int x) {
        Pixel::x = x;
    }

    int Pixel::getY() const {
        return y;
    }

    void Pixel::setY(int y) {
        Pixel::y = y;
    }

    bool Pixel::isIsTransperent() const {
        return isTransperent;
    }

    void Pixel::setIsTransperent(bool isTransperent) {
        Pixel::isTransperent = isTransperent;
    }

    Pixel::~Pixel() {

    }

}
