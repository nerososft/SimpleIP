//
//  Board.hpp
//  ai_hw
//
//  Created by neroyang on 2017/10/10.
//  Copyright © 2017年 neroyang. All rights reserved.
//

#ifndef OpenIP_Board_hpp
#define OpenIP_Board_hpp

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "StateBase.hpp"
#include "PixelMap.h"
#include "PNGLoader.h"
#include "Font.h"
#include "FpsLimter.h"
#include "System.h"
#include <vector>


namespace OpenIP {

    enum STATE{
        RENDERING,STOP
    };
    class Board : public StateBase {
    private:

        char *title;
        int width;
        int height;
        std::shared_ptr<ColorRGB> backGround;

        float _fps;

        int pid;

        STATE state;
        std::shared_ptr<FpsLimter> _fpsLimter = std::make_shared<FpsLimter>();
        Font* fps = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 5);
        Font*  fpsNum = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 5);

        std::shared_ptr<System> system = std::make_shared<System>();
        Font*  CPU = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 20);
        Font*  CPUNUM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 20);

        Font*   MEM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 35);
        Font*  MEMNUM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 35);


        std::shared_ptr<PNGLoader> pngLoader =std::make_shared<PNGLoader>(ALPHA::NO);
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> colorVector = pngLoader->loadPNG("photo.png",0,0);

        std::shared_ptr<PixelMap> yuantu;
        std::shared_ptr<PixelMap> huidu;
        std::shared_ptr<PixelMap> erzhi;
        std::shared_ptr<PixelMap> line;

    public:
        Board(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround);

        virtual void init();

        virtual void update();


        void renderFPS();
        void renderSysInfo();

        virtual void keycallback(
                GLFWwindow *window,
                int key,
                int scancode,
                int action,
                int mods);

        virtual void framebuffer_size_callback(GLFWwindow *window, int w, int h);

        void Render(void);

        int run();
    };

}
#endif /* Board_hpp */
