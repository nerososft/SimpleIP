//
// Created by neroyang on 2017/10/15.
//

#ifndef GP_HW_02_PNGLOADER_H
#define GP_HW_02_PNGLOADER_H


#include <vector>
#include "ColorRGB.h"
#include "PixelMap.h"

namespace  OpenIP {
    enum ALPHA{
        YES,NO
    };
    class PNGLoader {
    private:
        int width;
        int height;

        std::vector<std::vector<std::shared_ptr<ColorRGB>>> pixels;

        unsigned char *bgra;

        std::shared_ptr<PixelMap> pixelMap;

        ALPHA alpha;


    public:

        PNGLoader(ALPHA alpha);


        std::vector<std::vector<std::shared_ptr<ColorRGB>>> getPixelsMap() { return this->pixels; };

        int getWidth() { return this->width; };

        int getHeight() { return this->height; };


        std::vector<std::vector<std::shared_ptr<ColorRGB>>> loadPNG(char *filename,int w,int h);

        void loadPNGToPixelMap(char *filename,std::shared_ptr<PixelMap> pixelMap1);

        void colorVectorToPixelMap(std::vector<std::vector<std::shared_ptr<ColorRGB>>> colorVector,std::shared_ptr<PixelMap> pixelMap1);
    };
}

#endif //GP_HW_02_PNGLOADER_H
