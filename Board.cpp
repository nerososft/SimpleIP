//
//  Board.cpp
//  ai_hw
//
//  Created by neroyang on 2017/10/10.
//  Copyright © 2017年 neroyang. All rights reserved.
//

#include "Board.hpp"
#include <time.h>
#include <glu.h>
#include "Rectangle.hpp"
#include <algorithm>
#include <cmath>
#include "math.h"


Board::Board(char* title, int width, int height, ColorRGB *backGround) : title(title), width(width), height(height), backGround(backGround) {
    yuantu = new PixelMap(0,0,this->width/4,this->height/2,new ColorRGB(255,255,0));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel(i,j,pixelsMap[j][i]));
        }
        pixels.push_back(pp);
    }

    yuantu->setPixelMap(pixels);
    yuantu->normalize(width,height);

    zhongzhi =      new PixelMap((this->width/4),0,this->width/4,this->height/2,new ColorRGB(0,255,0));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)+i,j,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_zhong.push_back(pp);
    }

    for(int i  = 0;i<this->zhongzhi->getWidth();i++){
        for(int j = 0;j<this->zhongzhi->getHeight();j++){
            if(i>1 && i<this->zhongzhi->getWidth()-1 && j>1 && j<this->zhongzhi->getHeight()-1) {
                float gray[9];
                int index = 0;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        gray[index] = pixels[i+r][j+c]->getColor()->R()*0.03f +
                                pixels[i+r][j+c]->getColor()->G()*0.59f+
                                pixels[i+r][j+c]->getColor()->B()*0.11f;
                        index++;
                    }
                }
                Math* math = new Math();
                int len=sizeof(gray)/sizeof(int);
                math->quickSort(gray,0,len-1);
                float current_gray = gray[4]; //    灰度值中位数



                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        if(current_gray == pixels[i+r][j+c]->getColor()->R()*0.03f +
                                           pixels[i+r][j+c]->getColor()->G()*0.59f+
                                           pixels[i+r][j+c]->getColor()->B()*0.11f){

                            pixels_zhong[i][j]->setColor(pixels[i+r][j+c]->getColor());
                        }
                    }
                }
            }
        }
    }
    zhongzhi->setPixelMap(pixels_zhong);
    zhongzhi->normalize(width,height);


    zuidazhi =      new PixelMap((this->width/4)*2,0,this->width/4,this->height/2,new ColorRGB(255,0,0));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)*2+i,j,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_zuida.push_back(pp);
    }

    for(int i  = 0;i<this->zuidazhi->getWidth();i++){
        for(int j = 0;j<this->zuidazhi->getHeight();j++){
            if(i>1 && i<this->zuidazhi->getWidth()-1 && j>1 && j<this->zuidazhi->getHeight()-1) {
                float gray[9];
                int index = 0;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        gray[index] = pixels[i+r][j+c]->getColor()->R()*0.03f +
                                pixels[i+r][j+c]->getColor()->G()*0.59f+
                                pixels[i+r][j+c]->getColor()->B()*0.11f;
                        index++;
                    }
                }

                Math* math = new Math();
                int len=sizeof(gray)/sizeof(int);
                math->quickSort(gray,0,len-1);

                float current_gray = gray[8];
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        if(current_gray == pixels[i+r][j+c]->getColor()->R()*0.03f +
                                                   pixels[i+r][j+c]->getColor()->G()*0.59f+
                                                   pixels[i+r][j+c]->getColor()->B()*0.11f){

                            pixels_zuida[i][j]->setColor(pixels[i+r][j+c]->getColor());
                        }
                    }
                }
            }
        }
    }
    zuidazhi->setPixelMap(pixels_zuida);
    zuidazhi->normalize(width,height);

    zuixiaozhi =    new PixelMap((this->width/4)*3,0,this->width/4,this->height/2,new ColorRGB(0,255,255));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)*3+i,j,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_zuixiao.push_back(pp);
    }


    for(int i  = 0;i<this->zuixiaozhi->getWidth();i++){
        for(int j = 0;j<this->zuixiaozhi->getHeight();j++){
            if(i>1 && i<this->zuixiaozhi->getWidth()-1 && j>1 && j<this->zuidazhi->getHeight()-1) {
                float gray[9];
                int index = 0;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        gray[index] = pixels[i+r][j+c]->getColor()->R()*0.03f +
                                pixels[i+r][j+c]->getColor()->G()*0.59f+
                                pixels[i+r][j+c]->getColor()->B()*0.11f;
                        index++;
                    }
                }

                Math* math = new Math();
                int len=sizeof(gray)/sizeof(int);
                math->quickSort(gray,0,len-1);

                float current_gray = gray[0];
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        if(current_gray == pixels[i+r][j+c]->getColor()->R()*0.03f +
                                                   pixels[i+r][j+c]->getColor()->G()*0.59f+
                                                   pixels[i+r][j+c]->getColor()->B()*0.11f){

                            pixels_zuixiao[i][j]->setColor(pixels[i+r][j+c]->getColor());
                        }
                    }
                }
            }
        }
    }
    zuixiaozhi->setPixelMap(pixels_zuixiao);
    zuixiaozhi->normalize(width,height);


    suanshu =       new PixelMap(0,this->height/2,this->width/4,this->height/2,new ColorRGB(255,255,0));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel(i,j+this->height/2,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_suanshu.push_back(pp);

    }

    for(int i  = 0;i<this->suanshu->getWidth();i++){
        for(int j = 0;j<this->suanshu->getHeight();j++){
            if(i>1 && i<this->suanshu->getWidth()-1 && j>1 && j<this->suanshu->getHeight()-1) {
                float R = 0.0f,G = 0.0f,B = 0.0f;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        R+=pixels[i+r][j+c]->getColor()->R();
                        G+=pixels[i+r][j+c]->getColor()->G();
                        B+=pixels[i+r][j+c]->getColor()->B();
                    }
                }
                R = (R/9.0f)*255.0f;
                G = (G/9.0f)*255.0f;
                B = (B/9.0f)*255.0f;

                pixels_suanshu[i][j]->setColor(new ColorRGB(R,G,B));
            }
        }
    }

    suanshu->setPixelMap(pixels_suanshu);
    suanshu->normalize(width,height);


    jihe =          new PixelMap((this->width/4),this->height/2,this->width/4,this->height/2,new ColorRGB(0,255,255));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)+i,j+this->height/2,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_jihe.push_back(pp);
    }

    for(int i  = 0;i<this->jihe->getWidth();i++){
        for(int j = 0;j<this->jihe->getHeight();j++){
            if(i>1 && i<this->jihe->getWidth()-1 && j>1 && j<this->jihe->getHeight()-1) {
                float R = 1.0f,G = 1.0f,B = 1.0f;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        R*=(pixels[i+r][j+c]->getColor()->R()*255.0f);
                        G*=(pixels[i+r][j+c]->getColor()->G()*255.0f);
                        B*=(pixels[i+r][j+c]->getColor()->B()*255.0f);
                    }
                }

                R = pow(R,1.0f/9.0f);
                G = pow(G,1.0f/9.0f);
                B = pow(B,1.0f/9.0f);

                pixels_jihe[i][j]->setColor(new ColorRGB(R,G,B));
            }
        }
    }
    jihe->setPixelMap(pixels_jihe);
    jihe->normalize(width,height);

    xie =           new PixelMap((this->width/4)*2,this->height/2,this->width/4,this->height/2,new ColorRGB(255,0,255));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)*2+i,j+this->height/2,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_xie.push_back(pp);
    }

    for(int i  = 0;i<this->xie->getWidth();i++){
        for(int j = 0;j<this->xie->getHeight();j++){
            if(i>1 && i<this->xie->getWidth()-1 && j>1 && j<this->xie->getHeight()-1) {
                float R = 0.0f,G = 0.0f,B = 0.0f;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        R+=(1.0f/pixels[i+r][j+c]->getColor()->R());
                        G+=(1.0f/pixels[i+r][j+c]->getColor()->G());
                        B+=(1.0f/pixels[i+r][j+c]->getColor()->B());
                    }
                }
                R = (9.0f/R)*255.0f;
                G = (9.0f/G)*255.0f;
                B = (9.0f/B)*255.0f;
                pixels_xie[i][j]->setColor(new ColorRGB(R,G,B));
            }
        }
    }
    xie->setPixelMap(pixels_xie);
    xie->normalize(width,height);

    nixie =         new PixelMap((this->width/4)*3,this->height/2,this->width/4,this->height/2,new ColorRGB(255,255,255));
    for(int i = 0;i<this->width/4;i++){
        std::vector<Pixel*> pp;
        for(int j = 0;j<this->height/2;j++){
            pp.push_back(new Pixel((this->width/4)*3+i,j+this->height/2,new ColorRGB(i,j,(i*j)%255)));
        }
        pixels_niexie.push_back(pp);
    }

    for(int i  = 0;i<this->nixie->getWidth();i++){
        for(int j = 0;j<this->nixie->getHeight();j++){
            if(i>1 && i<this->nixie->getWidth()-1 && j>1 && j<this->nixie->getHeight()-1) {
                float R = 0.0f,G =0.0f,B=0.0f,R1 = 0.0f,G1 =0.0f,B1=0.0f;
                float Q = 0;
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        R+=(pow(pixels[i+r][j+c]->getColor()->R(),Q));
                        G+=(pow(pixels[i+r][j+c]->getColor()->G(),Q));
                        B+=(pow(pixels[i+r][j+c]->getColor()->B(),Q));
                    }
                }
                for(int r = -1;r<2;r++){
                    for(int c = -1;c<2;c++){
                        R1+=(pow(pixels[i+r][j+c]->getColor()->R(),Q+1.0f));
                        G1+=(pow(pixels[i+r][j+c]->getColor()->G(),Q+1.0f));
                        B1+=(pow(pixels[i+r][j+c]->getColor()->B(),Q+1.0f));
                    }
                }
                R = (R1/R)*255.0f;
                G = (G1/G)*255.0f;
                B = (B1/B)*255.0f;
                pixels_niexie[i][j]->setColor(new ColorRGB(R,G,B));
            }
        }
    }
    nixie->setPixelMap(pixels_niexie);
    nixie->normalize(width,height);
}

void Board::keycallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    update();
    if (action != GLFW_PRESS)
        return;
    switch (key) {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GL_TRUE);
            break;
        default:
            break;
    }
}

GLfloat ratio = 1.f;

void Board::framebuffer_size_callback(GLFWwindow *window, int w, int h) {
    if (h == 0)
    {
        h = 1;
    }
    if (h > 0) {
        ratio = (float) w / (float) h;
    }

    glViewport(0, 0, w, h);
    this->width = w;
    this->height = h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);

    update();
}


void Board::update() {
    yuantu->render();
    zhongzhi->render();
    zuidazhi->render();
    zuixiaozhi->render();

    suanshu->render();
    jihe->render();
    xie->render();
    nixie->render();

}

void Board::Render() {


        update();
}

int Board::run() {
    GLFWwindow *win;
    if (!glfwInit()) {
        return -1;
    }
    win = glfwCreateWindow(this->width, this->height, this->title, NULL, NULL);

    if (!win) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    if (!glewInit()) {
        return -1;
    }

    framebuffer_size_callback(win,this->width,this->height);

    glfwSetKeyCallback(win, StateBase::keycallback_dispatch);

    glfwSetFramebufferSizeCallback(win, StateBase::framebuffer_size_callback_dispatch);
    glfwMakeContextCurrent(win);

    while (!glfwWindowShouldClose(win)) {
        glClearColor(backGround->R(), backGround->G(), backGround->B(), 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Render();
        glfwSwapBuffers(win);
        glfwPollEvents();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}


