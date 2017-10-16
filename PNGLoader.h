//
// Created by neroyang on 2017/10/15.
//

#ifndef GP_HW_02_PNGLOADER_H
#define GP_HW_02_PNGLOADER_H


#include <vector>
#include "ColorRGB.h"

namespace  OpenIP {
    class PNGLoader {
    private:
        int width;
        int height;

        std::vector<std::vector<ColorRGB *>> pixels;

        unsigned char *bgra;


    public:


        PNGLoader();

        std::vector<std::vector<ColorRGB *>> getPixelsMap() { return this->pixels; };

        int getWidth() { return this->width; };

        int getHeight() { return this->height; };


        std::vector<std::vector<ColorRGB *>> loadPNG(char *filename);
    };
}

#endif //GP_HW_02_PNGLOADER_H
