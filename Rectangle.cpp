//
//  Rectangle.cpp
//  ai_hw
//
//  Created by neroyang on 2017/10/10.
//  Copyright © 2017年 neroyang. All rights reserved.
//

#include "Rectangle.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

Rectangle::Rectangle(float x,
                     float y,
                     float width,
                     float height,
                     float r,
                     float g,
                     float b):x(x),y(y),width(width),height(height),r(r),g(g),b(b){
    
}

void Rectangle::draw(){
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    {
        glVertex3f(x,    y,      0.0);
        glVertex3f(x+width,  y,      0.0);
        glVertex3f(x+width,  y+height, 0.0);
        glVertex3f(x,    y+height, 0.0);
    }
    glEnd();
}
