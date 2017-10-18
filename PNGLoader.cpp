//
// Created by neroyang on 2017/10/15.
//

#include <cstdio>
#include <png.h>
#include <iostream>
#include "PNGLoader.h"
namespace OpenIP {
    std::vector<std::vector<std::shared_ptr<ColorRGB>>> PNGLoader::loadPNG(char *filename) {
        FILE *file = fopen(filename, "rb");

        png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);

        png_infop info_ptr = png_create_info_struct(png_ptr);

        setjmp(png_jmpbuf(png_ptr));


        png_init_io(png_ptr, file);


        png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_EXPAND, 0);


        int m_width = png_get_image_width(png_ptr, info_ptr);
        int m_height = png_get_image_height(png_ptr, info_ptr);

        this->width = m_width;
        this->height = m_height;

        int color_type = png_get_color_type(png_ptr, info_ptr);


        int size = m_height * m_width * 4;

        this->bgra = new unsigned char[size];

        int pos = 0;


        png_bytep *row_pointers = png_get_rows(png_ptr, info_ptr);


        for (int i = 0; i < m_height; i++) {
            std::vector<std::shared_ptr<ColorRGB>> color;
            for (int j = 0; j < (4 * m_width); j += 4) {
                this->bgra[pos++] = row_pointers[i][j + 2]; // blue
                this->bgra[pos++] = row_pointers[i][j + 1]; // green
                this->bgra[pos++] = row_pointers[i][j];   // red
                this->bgra[pos++] = row_pointers[i][j + 3]; // alpha

                color.push_back(std::make_shared<ColorRGB>(row_pointers[i][j], row_pointers[i][j + 1], row_pointers[i][j + 2]));
            }
            pixels.push_back(color);
        }

        png_destroy_read_struct(&png_ptr, &info_ptr, 0);

        fclose(file);

        return pixels;
    }

    void  PNGLoader::loadPNGToPixelMap(char *filename,std::shared_ptr<PixelMap> pixelMap1){
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> pixelsMap = loadPNG(filename);
        pixelMap1->setWidth(this->width);
        pixelMap1->setHeight(this->height);
        std::vector<std::vector<std::shared_ptr<Pixel>>> pixels;
        for (int i = 0; i < this->width; i++) {
            std::vector<std::shared_ptr<Pixel>> pp;
            for (int j = 0; j < this->height; j++) {
                pp.push_back(std::make_shared<Pixel>(pixelMap1->getX()+i, pixelMap1->getY()+j, pixelsMap[j][i]));
            }
            pixels.push_back(pp);
        }
        pixelMap1->setPixelMap(pixels);
    }

    void PNGLoader::colorVectorToPixelMap(std::vector<std::vector<std::shared_ptr<ColorRGB >>> colorVector,std::shared_ptr<PixelMap> pixelMap1){
        pixelMap1->setWidth(this->width);
        pixelMap1->setHeight(this->height);
        std::vector<std::vector<std::shared_ptr<Pixel>>> pixels;
        for (int i = 0; i < this->width; i++) {
            std::vector<std::shared_ptr<Pixel>> pp;
            for (int j = 0; j < this->height; j++) {
                pp.push_back(std::make_shared<Pixel>(pixelMap1->getX()+i, pixelMap1->getY()+j, colorVector[j][i]));
            }
            pixels.push_back(pp);
        }
        pixelMap1->setPixelMap(pixels);
    }

    PNGLoader::PNGLoader() {
        this->width = 160;
        this->height = 240;
    }
}