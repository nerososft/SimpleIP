//
// Created by neroyang on 2017/10/25.
//

#ifndef GP_HW_02_GO_H
#define GP_HW_02_GO_H

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
#include "network/HttpService.h"
#include <vector>

namespace OpenIP {

    extern  int map[19][19];
    extern float qi[19][19];
    extern float yinxiang[19][19];

    class Go : public StateBase {
    private:

        float c_xpos;
        float c_ypos;

        char *title;
        int width;
        int height;
        std::shared_ptr<ColorRGB> backGround;

        std::shared_ptr<FpsLimter> _fpsLimter = std::make_shared<FpsLimter>();

        std::shared_ptr<PNGLoader> boardLoader =std::make_shared<PNGLoader>(ALPHA::NO);
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> colorVector = boardLoader->loadPNG("weiqiboard.png",0,0);

        std::shared_ptr<PNGLoader> heiLoader =std::make_shared<PNGLoader>(ALPHA::YES);
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> heicolorVector = heiLoader->loadPNG("hei_back.png",0,0);

        std::shared_ptr<PNGLoader> baiLoader =std::make_shared<PNGLoader>(ALPHA::YES);
        std::vector<std::vector<std::shared_ptr<ColorRGB>>> baicolorVector = baiLoader->loadPNG("bai_back.png",0,0);

        std::shared_ptr<PixelMap> qipan;

        std::shared_ptr<PixelMap> heiqi;
        std::shared_ptr<PixelMap> baiqi;


        int blockLength;
        int* block;


        bool isWhite = true;
        std::vector<std::vector<std::shared_ptr<PixelMap>>> pixel_map;

        std::vector<std::vector<std::shared_ptr<PixelMap>>> network;

        std::shared_ptr<HttpService>  httpservice = std::make_shared<HttpService>();

    public:




        Go(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround);

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
        virtual void mouse_button_callback(GLFWwindow* window, int button, int action, int mod);
        virtual void cursor_position_callback(GLFWwindow* window, double x, double y);

        void Render(void);

        bool check_is_no_qi(int x,int y); //检查落子位置是否无气
        void check_chizi(int x,int y); //吃子
        bool check_is_qi(int x,int y);//当前位置是否有棋子




        void recursion(int i,int j);
        void kill();
        bool hasQi();
        bool isInBlock(int neighbor);

        void RenderQiPan();

        int run();
    };

}
#endif //GP_HW_02_GO_H
