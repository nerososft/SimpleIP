//
// Created by neroyang on 2017/10/14.
//

#ifndef GP_HW_02_PIXEL_H
#define GP_HW_02_PIXEL_H


#include "ColorRGB.h"
#include "Rectangle.hpp"

namespace OpenIP {
    class Pixel {

    private:
        int x;
        int y;
        std::shared_ptr<ColorRGB> color;
        std::shared_ptr<Rectangle> rectangle;
        bool isTransperent = false;

    public:
        Pixel(int x, int y, std::shared_ptr<ColorRGB> color);


        std::shared_ptr<ColorRGB> getColor() { return this->color; };


        void setColor(std::shared_ptr<ColorRGB> color) { this->rectangle->setColor(color->R(), color->G(), color->B()); };


        void normalize(int width, int height);

        int getX() const;

        void setX(int x);

        int getY() const;

        void setY(int y);

        void render();

        bool isIsTransperent() const;

        void setIsTransperent(bool isTransperent);

        virtual ~Pixel();
    };
}

#endif //GP_HW_02_PIXEL_H
