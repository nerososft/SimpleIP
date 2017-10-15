//
// Created by neroyang on 2017/10/14.
//

#ifndef GP_HW_02_PIXEL_H
#define GP_HW_02_PIXEL_H


#include "ColorRGB.h"
#include "Rectangle.hpp"

class Pixel {

private:
    int x;
    int y;
    ColorRGB* color;
    Rectangle *rectangle;

public:
    Pixel(int x, int y, ColorRGB *color);


    ColorRGB* getColor(){return this->color;};


    void setColor(ColorRGB* color){this->rectangle->setColor(color->R(),color->G(),color->B());};


    void normalize(int width,int height);


    void render();
};


#endif //GP_HW_02_PIXEL_H
