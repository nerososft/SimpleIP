//
// Created by neroyang on 2017/10/16.
//

#include "Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include <freetype/freetype.h>
#include <freetype/ftglyph.h>
#include <freetype/ftcache.h>

namespace OpenIP{
    Font::Font(char *ttfPath, FONT_MODE font_mode,  std::shared_ptr<ColorRGB> foreColor, std::shared_ptr<ColorRGB> backColor, int width, int height, int x, int y) : ttfPath(ttfPath), font_mode(font_mode), foreColor(foreColor), backColor(backColor), width(width), height(height), x(x),
                                                                                                                                     y(y) {
        error  =  FT_Init_FreeType( & pFTLib);
        if (error)
        {
            pFTLib  =   0 ;
            printf( " There is some error when Init Library " );
        }

        error  =  FT_New_Face(pFTLib,  this->ttfPath ,  0 ,  & pFTFace);
        if (error)
        {
            printf( " There is some error when Init Library " );
        }
    }

    std::shared_ptr<PixelMap> Font::getCharPixelMap(char c) {

            FT_Set_Char_Size(pFTFace,  16 << 6 ,  16 << 6 ,  this->width ,  this->height );
            FT_Glyph    glyph;

            FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace,  int(c) ), FT_LOAD_DEFAULT);
            error  =  FT_Get_Glyph(pFTFace -> glyph,  & glyph);
            std::shared_ptr<PixelMap> fontPixels;

            if ( ! error)
            {
                FT_Glyph_To_Bitmap( & glyph, ft_render_mode_normal,  0 ,  1 );
                FT_BitmapGlyph    bitmap_glyph  =  (FT_BitmapGlyph)glyph;
                FT_Bitmap &     bitmap  =  bitmap_glyph -> bitmap;

                bitMapWidth = bitmap.width;
                bitmapHeight = bitmap.rows;

                charLenV.push_back(bitMapWidth);

                fontPixels = std::make_shared<PixelMap>(x,y,bitmap.rows,bitmap.width,backColor);

                std::vector<std::vector<std::shared_ptr<Pixel>>> font;

                for ( int  i = 0 ; i < bitmap.rows;  ++ i)
                {
                    std::vector<std::shared_ptr<Pixel>> fo;
                    for ( int  j = 0 ; j < bitmap.width;  ++ j)
                    {
                        if(bitmap.buffer[i * bitmap.width + j]){
                            std::shared_ptr<Pixel> pixel = std::make_shared<Pixel>(x + j, y + i, foreColor);
                            fo.push_back(pixel);
                        }else{
                            std::shared_ptr<Pixel> pixel = std::make_shared<Pixel>(x + j, y + i, backColor);
                            if(this->font_mode==FONT_MODE::TRANSPARENT) {
                                pixel->setIsTransperent(true);
                            }
                            fo.push_back(pixel);
                        }
                    }
                    font.push_back(fo);
                }

                fontPixels->setPixelMap(font);
                fontPixels->flipUpDown();

                FT_Done_Glyph(glyph);
                glyph  =  NULL;
            }

        return fontPixels;
    }

    void Font::normalize(int width, int height){
        for(int i = 0;i<charLen;i++) {
            this->stringPixels[i]->normalize(width, height);
        }
    }

    void Font::draw(const char* ch){
        stringPixels.clear();
        charLenV.clear();
        charLen = 0;

        int charNum = strlen(ch);
        charLen = charNum;
        for(int i = 0;i<charNum;i++){
            std::shared_ptr<PixelMap> pp = getCharPixelMap(ch[i]);
            if(i!=0) {
                int w = 0;
                for(int j = 0;j<i;j++){
                    w+=charLenV[j]+spacing;
                }
                pp->setX(w);
            }
            stringPixels.push_back(pp);
        }

    }

    void Font::render(){
        for(int i = 0;i<charLen;i++){
            this->stringPixels[i]->render();
        }
    }



    int Font::getSpacing() const {
        return spacing;
    }

    void Font::setSpacing(int spacing) {
        Font::spacing = spacing;
    }

    Font::~Font() {
        FT_Done_Face(pFTFace);
        pFTFace  =  NULL;
        FT_Done_FreeType(pFTLib);
        pFTLib = NULL;
    }
}