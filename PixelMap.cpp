//
// Created by neroyang on 2017/10/14.
//

#include "PixelMap.h"

namespace OpenIP {
    void PixelMap::normalize(int width, int height) {
        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->height; j++) {
                pixelMap[i][j]->normalize(width, height);
            }
        }
    }

    void PixelMap::render() {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                pixelMap[i][j]->render();
            }
        }
    }

    PixelMap::PixelMap(int x, int y, int width, int height, ColorRGB *backgroundColor) : x(x), y(y), height(height), width(width), backgroundColor(backgroundColor) {
        for (int i = 0; i < width; i++) {
            std::vector<Pixel *> pp;
            for (int j = 0; j < height; j++) {
                pp.push_back(new Pixel(x + i, y + j, backgroundColor));
            }
            pixelMap.push_back(pp);
        }
    }

    void PixelMap::changeColor(int i,int j,ColorRGB* color){
        this->pixelMap[i][j]->setColor(color);
    }

}
