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
#include "filter/Fliter.h"
#include "FpsLimter.h"
#include "segmentation/Segmentation.h"


namespace OpenIP {
    Board::Board(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround) :
            title(title),
            width(width),
            height(height),
            backGround(backGround) {
        _fps = 0.0f;
        state = STATE::RENDERING;
        _fpsLimter->init(60.0f);
        pid = system->get_pid("gp_hw_02","neroyang");

        init();

    }

    void Board::init(){
        fps->setSpacing(2);
        fps->draw("FPS:");
        fps->normalize(width, height);

        fpsNum->setSpacing(2);


        CPU->setSpacing(2);
        CPU->draw("CPU:");
        CPU->normalize(width, height);
        CPUNUM->setSpacing(2);


        MEM->setSpacing(2);
        MEM->draw("MEM:");
        MEM->normalize(width, height);
        MEMNUM->setSpacing(2);

        yuantu = std::make_shared<PixelMap>(0,0,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,yuantu);
        yuantu->normalize(width,height);

        huidu = std::make_shared<PixelMap>(160,0,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,huidu);
        std::shared_ptr<Fliter> huiduFilter = std::make_shared<Fliter>(huidu);
        huidu = huiduFilter->gray();
        huidu->normalize(width,height);

        erzhi = std::make_shared<PixelMap>(320,0,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,erzhi);
        std::shared_ptr<Fliter> erzhiFilter = std::make_shared<Fliter>(erzhi);
        erzhi = erzhiFilter->gray();
        std::shared_ptr<Segmentation> erzhiSegmentation = std::make_shared<Segmentation>(erzhi);
                erzhiSegmentation->setOptr(OPERATOR::Sobel);
                erzhiSegmentation->setDistanceThreshold(0.6);
        erzhi = erzhiSegmentation->convolution();
        erzhi->normalize(width,height);


        line = std::make_shared<PixelMap>(480,0,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,line);
        std::shared_ptr<Segmentation> lineSegmentation = std::make_shared<Segmentation>(line);
                    lineSegmentation->setOptr(OPERATOR::Sobel);
                    lineSegmentation->setDistanceThreshold(0.6);
        line =      lineSegmentation->convolution();
                    lineSegmentation->setMethodType(FUNC::LSF);
                    lineSegmentation->setLineColor(std::make_shared<ColorRGB>(255,0,0));
        line =      lineSegmentation->beelineFitting();
        line->normalize(width,height);

        ransac = std::make_shared<PixelMap>(0,240,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,ransac);
        std::shared_ptr<Segmentation> ransacSegmentation = std::make_shared<Segmentation>(ransac);
                    ransacSegmentation->setOptr(OPERATOR::Sobel);
                    ransacSegmentation->setDistanceThreshold(0.6);
        ransac =    ransacSegmentation->convolution();
                    ransacSegmentation->setMethodType(FUNC::LSF);
                    ransacSegmentation->setLineColor(std::make_shared<ColorRGB>(255,0,0));
        ransac =    ransacSegmentation->beelineFitting();
        ransac->normalize(width,height);

        hough = std::make_shared<PixelMap>(160,240,160,240,std::make_shared<ColorRGB>(0,0,0));
        pngLoader->colorVectorToPixelMap(colorVector,hough);
        std::shared_ptr<Segmentation> houghSegmentation = std::make_shared<Segmentation>(hough);
                    houghSegmentation->setOptr(OPERATOR::Sobel);
                    houghSegmentation->setDistanceThreshold(0.6);
        hough =     houghSegmentation->convolution();
                    houghSegmentation->setMethodType(FUNC::LSF);
                    houghSegmentation->setLineColor(std::make_shared<ColorRGB>(255,0,0));
        hough =     houghSegmentation->beelineFitting();
        hough->normalize(width,height);

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
        huidu->render();

        erzhi->render();
        line->render();

        ransac->render();

        hough->render();

        //renderFPS();
        //renderSysInfo();


    }

    void Board::renderFPS() {
        std::ostringstream buffer;
        buffer << _fps;
        std::string str = buffer.str();
        const char *ff = str.c_str();
        fps->render();
        fpsNum->draw(ff);
        fpsNum->normalize(width, height);
        fpsNum->render();
    }

    void Board::renderSysInfo() {
        CPU->render();
        CPUNUM->draw(system->get_proc_cpu(pid));
        CPUNUM->normalize(width,height);
        CPUNUM->render();

        MEM->render();
        MEMNUM->draw(system->get_proc_mem(pid));
        MEMNUM->normalize(width, height);
        MEMNUM->render();
    }

    void Board::Render() {
        if (state == STATE::RENDERING) {
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

