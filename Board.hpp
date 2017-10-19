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
        Font* fps = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 460);
        Font*  fpsNum = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 460);

        std::shared_ptr<System> system = std::make_shared<System>();
        Font*  CPU = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 445);
        Font*  CPUNUM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 445);

        Font*   MEM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,10, 430);
        Font*  MEMNUM = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,255), std::make_shared<ColorRGB>(0,255,0), 60, 60,60, 430);

        std::shared_ptr<PNGLoader> pngLoader =std::make_shared<PNGLoader>();
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> colorVector = pngLoader->loadPNG("yz.png");

        std::shared_ptr<PixelMap> yuantu;       //原图
        std::shared_ptr<PixelMap>  zhongzhi;     //中值滤波
        std::shared_ptr<PixelMap> zuidazhi;     //最大值
        std::shared_ptr<PixelMap>  zuixiaozhi;   //最小值

        std::shared_ptr<PixelMap>  suanshu;      //算数均值
        std::shared_ptr<PixelMap> jihe;         //几何均值
        std::shared_ptr<PixelMap>  xie;          //谐波
        std::shared_ptr<PixelMap>  nixie;        //逆谐波


        Font*  Open = new Font("default.otf", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(255,255,255), std::make_shared<ColorRGB>(0,255,0), 500, 500,100, 200);
        Font*  IP = new Font("ip2.TTF", FONT_MODE::TRANSPARENT,std::make_shared<ColorRGB>(0,255,0), std::make_shared<ColorRGB>(0,255,0), 500, 500,400, 200);



    public:
        Board(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround);


        void update();


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
