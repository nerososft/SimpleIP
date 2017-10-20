//
// Created by neroyang on 2017/10/14.
//

#include <iostream>
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
                if(!pixelMap[i][j]->isIsTransperent()) {
                    pixelMap[i][j]->render();
                }
            }
        }
    }

    PixelMap::PixelMap(int x, int y, int width, int height, std::shared_ptr<ColorRGB> backgroundColor) :
            x(x),
            y(y),
            height(height),
            width(width),
            backgroundColor(backgroundColor) {
        for (int i = 0; i < width; i++) {
            std::vector<std::shared_ptr<Pixel>> pp;
            for (int j = 0; j < height; j++) {
                pp.push_back(std::make_shared<Pixel>(x + i, y + j, backgroundColor));
            }
            pixelMap.push_back(pp);
        }
    }

    void PixelMap::changeColor(int i,int j,std::shared_ptr<ColorRGB> color){
        this->pixelMap[i][j]->setColor(color);
    }

    int PixelMap::getX() const {
        return x;
    }

    void PixelMap::setX(int x) {
        PixelMap::x = x;
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                pixelMap[i][j]->setX(x+pixelMap[i][j]->getX());
            }
        }
    }

    int PixelMap::getY() const {
        return y;
    }

    void PixelMap::setY(int y) {
        PixelMap::y = y;
    }

    int PixelMap::getHeight() const {
        return height;
    }

    void PixelMap::setHeight(int height) {
        PixelMap::height = height;
    }

    int PixelMap::getWidth() const {
        return width;
    }

    void PixelMap::setWidth(int width) {
        PixelMap::width = width;
    }

    std::shared_ptr<ColorRGB> PixelMap::getBackgroundColor() const {
        return backgroundColor;
    }

    void PixelMap::setBackgroundColor(std::shared_ptr<ColorRGB> backgroundColor) {
        PixelMap::backgroundColor = backgroundColor;
    }

    void PixelMap::flipUpDown(){
        int temp;
        int i,j;
        for (i=0; i<(width/2); i++) {
            for (j=0; j<height; j++) {
                temp = pixelMap[i][j]->getY();
                pixelMap[i][j]->setY(pixelMap[width-i-1][j]->getY());
                pixelMap[width-i-1][j]->setY(temp);
            }
        }
    }

    PixelMap::~PixelMap() {
    }

}
