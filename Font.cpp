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

    void Font::loadFont(){
    }

    void Font::draw(char c){
        error  =  FT_Init_FreeType( & pFTLib);
        if (error)
        {
            pFTLib  =   0 ;
            printf( " There is some error when Init Library " );
        }

        error  =  FT_New_Face(pFTLib,  "default.otf" ,  0 ,  & pFTFace);
        if ( ! error)
        {

            FT_Set_Char_Size(pFTFace,  16 << 6 ,  16 << 6 ,  this->width ,  this->height );
            FT_Glyph    glyph;
            //  load glyph 'C'
            FT_Load_Glyph(pFTFace, FT_Get_Char_Index(pFTFace,  int(c) ), FT_LOAD_DEFAULT);
            error  =  FT_Get_Glyph(pFTFace -> glyph,  & glyph);
            if ( ! error)
            {
                //  convert glyph to bitmap with 256 gray
                FT_Glyph_To_Bitmap( & glyph, ft_render_mode_normal,  0 ,  1 );
                FT_BitmapGlyph    bitmap_glyph  =  (FT_BitmapGlyph)glyph;
                FT_Bitmap &     bitmap  =  bitmap_glyph -> bitmap;


                fontPixels = new PixelMap(x,y,bitmap.rows,bitmap.width,backColor);
                std::vector<std::vector<Pixel*>> font;

                for ( int  i = 0 ; i < bitmap.rows;  ++ i)
                {
                    std::vector<Pixel*> fo;
                    for ( int  j = 0 ; j < bitmap.width;  ++ j)
                    {
                        //  if it has gray>0 we set show it as 1, o otherwise
                        if(bitmap.buffer[i * bitmap.width + j]){
                            fo.push_back(new Pixel(x+i,y+j,foreColor));
                        }else{
                            fo.push_back(new Pixel(x+i,y+j,backColor));
                        }
                        //printf( " %d " , bitmap.buffer[i * bitmap.width + j] ? 1 : 0 );
                    }
                    font.push_back(fo);
                }

                fontPixels->setPixelMap(font);
                FT_Done_Glyph(glyph);
                glyph  =  NULL;
            }

            FT_Done_Face(pFTFace);
            pFTFace  =  NULL;
        }


        FT_Done_FreeType(pFTLib);
        pFTLib  =  NULL;
    }
    void Font::normalize(int width, int height){
        this->fontPixels->normalize(width,height);
    }

    void Font::draw(char* ch){

    }

    void Font::render(){
        this->fontPixels->render();
    }

    Font::Font(char *ttfPath, FONT_MODE font_mode,  ColorRGB *foreColor, ColorRGB *backColor, int width, int height, int x, int y) : ttfPath(ttfPath), font_mode(font_mode), fontPixels(fontPixels), foreColor(foreColor), backColor(backColor), width(width), height(height), x(x),
                                                                                                                                                          y(y) {}


}