//
// Created by neroyang on 2017/10/15.
//

#ifndef GP_HW_02_PNGLOADER_H
#define GP_HW_02_PNGLOADER_H


#include <vector>
#include "ColorRGB.h"
#include "PixelMap.h"

namespace  OpenIP {
    class PNGLoader {
    private:
        int width;
        int height;

        std::vector<std::vector<ColorRGB *>> pixels;

        unsigned char *bgra;

        PixelMap* pixelMap;


    public:


        PNGLoader();

        std::vector<std::vector<ColorRGB *>> getPixelsMap() { return this->pixels; };

        int getWidth() { return this->width; };

        int getHeight() { return this->height; };


        std::vector<std::vector<ColorRGB *>> loadPNG(char *filename);

        void loadPNGToPixelMap(char *filename,PixelMap* pixelMap1);

        void colorVectorToPixelMap(std::vector<std::vector<ColorRGB *>> colorVector,PixelMap* pixelMap1);
    };
}

#endif //GP_HW_02_PNGLOADER_H
