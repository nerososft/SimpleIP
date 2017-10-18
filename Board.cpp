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
#include <sstream>
#include "math.h"
#include "Fliter.h"
#include "FpsLimter.h"


namespace OpenIP {
    Board::Board(char *title, int width, int height, ColorRGB *backGround) : title(title), width(width), height(height), backGround(backGround) {
        _fps = 0.0f;
        state = STATE::RENDERING;
        _fpsLimter->init(60.0f);

        yuantu = new PixelMap(0, 0, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,yuantu);
        yuantu->normalize(width, height);


        zhongzhi = new PixelMap((this->width / 4), 0, this->width / 4, this->height / 2, new ColorRGB(255, 0, 255));
        pngLoader->colorVectorToPixelMap(colorVector,zhongzhi);
        Fliter* fliter = new Fliter(zhongzhi);
        zhongzhi = fliter->median();
        zhongzhi->normalize(width, height);


        zuidazhi = new PixelMap((this->width / 4) * 2, 0, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,zuidazhi);
        Fliter* fliterzuida = new Fliter(zuidazhi);
        zuidazhi = fliterzuida->max();
        zuidazhi->normalize(width, height);

        zuixiaozhi = new PixelMap((this->width / 4) * 3, 0, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,zuixiaozhi);
        Fliter* fliterzuixiao = new Fliter(zuixiaozhi);
        zuixiaozhi = fliterzuixiao->min();
        zuixiaozhi->normalize(width, height);


        suanshu = new PixelMap(0, this->height / 2, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,suanshu);
        Fliter* flitersuanshu = new Fliter(suanshu);
        suanshu = flitersuanshu->arithmetic_mean();
        suanshu->normalize(width, height);


        jihe = new PixelMap((this->width / 4), this->height / 2, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,jihe);
        Fliter* fliterjihe = new Fliter(jihe);
        jihe = fliterjihe->geometric_mean();
        jihe->normalize(width, height);

        xie = new PixelMap((this->width / 4) * 2, this->height / 2, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,xie);
        Fliter* fliterxie = new Fliter(xie);
        xie = fliterxie->harmonics();
        xie->normalize(width, height);

        nixie = new PixelMap((this->width / 4) * 3, this->height / 2, this->width / 4, this->height / 2, new ColorRGB(255, 255, 255));
        pngLoader->colorVectorToPixelMap(colorVector,nixie);
        Fliter* fliternixie = new Fliter(nixie);
        nixie = fliternixie->inverse_harmonic();
        nixie->normalize(width, height);


        fps->setSpacing(2);
        fps->draw("FPS:");
        fps->normalize(width,height);

        fpsNum->setSpacing(2);

        Open->draw("Open");
        Open->normalize(width,height);
        IP->draw("IP");
        IP->normalize(width,height);

        CPU->setSpacing(2);
        CPU->draw("CPU:");
        CPU->normalize(width,height);
        CPUNUM->setSpacing(2);


        MEM->setSpacing(2);
        MEM->draw("MEM:");
        MEM->normalize(width,height);
        MEMNUM->setSpacing(2);

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
        if (h == 0) {
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

            Open->render();
            IP->render();
            fps->render();

            renderFPS();
        renderSysInfo();

    }


    void Board::renderFPS(){
        std::ostringstream buffer;
        buffer << _fps;
        std::string str = buffer.str();
        const char* ff= str.c_str();

        fpsNum->draw(ff);
        fpsNum->normalize(width,height);
        fpsNum->render();
    }
    void Board::renderSysInfo(){
        CPU->render();

        CPUNUM->draw("0%");
        CPUNUM->normalize(width,height);
        CPUNUM->render();

        MEM->render();
        MEMNUM->draw("0M");
        MEMNUM->normalize(width,height);
        MEMNUM->render();
    }
    void Board::Render() {
        if(state==STATE::RENDERING) {
            _fpsLimter->begin();
            update();
            _fps = _fpsLimter->end();
        }
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

        framebuffer_size_callback(win, this->width, this->height);

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

}

