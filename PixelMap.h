//
// Created by neroyang on 2017/10/14.
//

#ifndef GP_HW_02_PIXELMAP_H
#define GP_HW_02_PIXELMAP_H

#include <vector>
#include "ColorRGB.h"
#include "Pixel.h"
namespace OpenIP {
    class PixelMap {
    private:
        int x;
        int y;

        int height;
        int width;

        ColorRGB *backgroundColor;
        std::vector<std::vector<Pixel *>> pixelMap;

    public:

        void setPixelMap(std::vector<std::vector<Pixel *>> pixelmap) {
            this->pixelMap = pixelmap;
        };

        void changeColor(int i,int j,ColorRGB* color);

        void normalize(int width, int height);

        std::vector<std::vector<Pixel *>> getPixelMap() { return this->pixelMap; };

        PixelMap(int x, int y, int width, int height, ColorRGB *backgroundColor);

        void render();

        int getX() const;

        void setX(int x);

        int getY() const;

        void setY(int y);

        int getHeight() const;

        void setHeight(int height);

        int getWidth() const;

        void setWidth(int width);

        ColorRGB *getBackgroundColor() const;

        void setBackgroundColor(ColorRGB *backgroundColor);
    };
}



#endif //GP_HW_02_PIXELMAP_H
