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

        std::shared_ptr<ColorRGB> backgroundColor;
        std::vector<std::vector<std::shared_ptr<Pixel>>> pixelMap;

    public:

        void setPixelMap(std::vector<std::vector<std::shared_ptr<Pixel>>> pixelmap) {
            this->pixelMap = pixelmap;
        };

        void changeColor(int i,int j,std::shared_ptr<ColorRGB> color);

        void normalize(int width, int height);

        void flipUpDown();

        std::vector<std::vector<std::shared_ptr<Pixel>>> getPixelMap() { return this->pixelMap; };

        PixelMap(int x, int y, int width, int height, std::shared_ptr<ColorRGB> backgroundColor);

        void render();

        int getX() const;

        void setX(int x);

        int getY() const;

        void setY(int y);

        int getHeight() const;

        void setHeight(int height);

        int getWidth() const;

        void setWidth(int width);

        std::shared_ptr<ColorRGB> getBackgroundColor() const;

        void setBackgroundColor(std::shared_ptr<ColorRGB> backgroundColor);

        virtual ~PixelMap();
    };
}



#endif //GP_HW_02_PIXELMAP_H
