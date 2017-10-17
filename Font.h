//
// Created by neroyang on 2017/10/16.
//

#ifndef GP_HW_02_FONT_H
#define GP_HW_02_FONT_H

#include <freetype/freetype.h>
#include <string>
#include "PixelMap.h"


namespace OpenIP {

    enum FONT_MODE{
        TRANSPARENT = 0,
        SOLID = 1
    };
    class Font {

    private:
        char* ttfPath;

        FONT_MODE  font_mode;

        PixelMap* fontPixels;

        ColorRGB* foreColor;

        ColorRGB* backColor;

        int width;
        int height;

        int x;
        int y;

        FT_Library    pFTLib         =  NULL;
        FT_Face        pFTFace         =  NULL;
        FT_Error    error         =   0 ;


    public:
        void loadFont();

        void draw(char c);

        void draw(char* ch);

        void render();

        void normalize(int width, int height);

        Font(char *ttfPath, FONT_MODE font_mode, ColorRGB *foreColor, ColorRGB *backColor, int width, int height, int x, int y);
    };
}


#endif //GP_HW_02_FONT_H
