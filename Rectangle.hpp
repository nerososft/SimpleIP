//
//  Rectangle.hpp
//  ai_hw
//
//  Created by neroyang on 2017/10/10.
//  Copyright © 2017年 neroyang. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include <stdio.h>
namespace OpenIP {
    class Rectangle {
    private:

        float x;
        float y;

        float width;
        float height;

        float r;
        float g;
        float b;

    public:
        Rectangle(float x,
                  float y,
                  float width,
                  float height,
                  float r,
                  float g,
                  float b);

        void setX(float x) {
            this->x = x;
        };

        void setY(float y) {
            this->y = y;
        };

        void setWidth(float width) {
            this->width = width;
        };

        void setHeight(float height) {
            this->height = height;
        };

        void setColor(float r, float g, float b) {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        void draw();
    };
}
#endif /* Rectangle_hpp */
