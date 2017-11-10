//
//  Board.cpp
//  ai_hw
//
//  Created by neroyang on 2017/10/10.
//  Copyright © 2017年 neroyang. All rights reserved.
//

#include "go.h"
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

    int map[19][19];
    float qi[19][19];
    float yinxiang[19][19];

    Go::Go(char *title, int width, int height, std::shared_ptr<ColorRGB> backGround) :
            title(title),
            width(width),
            height(height),
            backGround(backGround) {
        init();

    }

    void Go::init(){
        for(int i = 0;i<19;i++){
            for(int j = 0;j<19;j++){

                map[i][j] = 0;
                if(     (i == 0 && j==0) ||
                        (i==18 && j==18) ||
                        (i==0  && j==18) ||
                        (i==18 && j==0)) {

                    qi[i][j] = 2;
                }/*上下左右四角气为2*/else if(
                        (i == 0  && j!=0 && j!=18) ||
                        (i == 18 && j!=0 && j!=18) ||
                        (j == 0  && i!=0 && i!=18) ||
                        (j == 18 && i!=0 && i!=18)){
                    qi[i][j] = 3;
                }/*四边界气为3*/else{
                    qi[i][j] = 4;
                }/*中间气为四*/
            }
        }

        qipan = std::make_shared<PixelMap>(0,0,1024,1024,std::make_shared<ColorRGB>(0,0,0));
        boardLoader->colorVectorToPixelMap(colorVector,qipan);
        qipan->normalize(width,height);

        httpservice->child_thread();
    }



    void Go::keycallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
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

    void Go::framebuffer_size_callback(GLFWwindow *window, int w, int h) {
        glViewport(0, 0, w, h);
        this->width = w;
        this->height = h;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);

        update();
    }

    void Go::mouse_button_callback(GLFWwindow* window, int button, int action, int mod){
        if (action == GLFW_PRESS) switch(button)
            {
                case GLFW_MOUSE_BUTTON_LEFT: {

                    int x = floor((c_xpos - 20) / 52);
                    int y = floor((c_ypos - 20) / 52);
                    if(check_is_qi(x,y) && check_is_no_qi(x,y)) { //检查落子位置是否无气
                        if (isWhite) {
                            map[x][y] = 1;
                            isWhite = false;
                        } else if (!isWhite) {
                            map[x][y] = -1;
                            isWhite = true;
                        }
                        kill();

                        //check_chizi(x, y);//检查吃子
                    }
                    break;
                }
                case GLFW_MOUSE_BUTTON_MIDDLE:
                    std::cout<<"Mosue middle button clicked!"<<std::endl;
                    break;
                case GLFW_MOUSE_BUTTON_RIGHT:
                    std::cout<<"Mosue right button clicked!"<<std::endl;
                    break;
                default:
                    return;
            }
        return;
    }


    void Go::cursor_position_callback(GLFWwindow* window, double x, double y){
        //std::cout<<"Mouse position move to "<<2*x<<":"<<2*y<<std::endl;
        c_xpos  =   floor(2*x);
        c_ypos  =   floor(2*y);
        return;
    }


    bool Go::check_is_no_qi(int x,int y){

        if(qi[x][y]==0){
            //无气，不可落子
            return false;
        }
        return true;

    } //检查落子位置是否无气

    bool Go::check_is_qi(int x,int y){
        if(map[x][y]==0){
            return true;
        }
        return false;
    }//当前位置是否有棋子

    void Go::check_chizi(int x,int y) {
    }

    void Go::RenderQiPan(){
        for(int i = 0;i<19;i++){
            for(int j = 0;j<19;j++){
                switch (map[i][j]){
                    case -1:{
                        std::shared_ptr<PixelMap> ptr = std::make_shared<PixelMap>(20 + 52 * i, 20 + 52 * j, 48, 48, std::make_shared<ColorRGB>(0, 0, 0));
                        heiLoader->colorVectorToPixelMap(heicolorVector, ptr);
                        ptr->normalize(width,height);
                        ptr->render();

                        std::shared_ptr<PixelMap> ptr2 = std::make_shared<PixelMap>(1050+10* i, 10* j, 10, 10, std::make_shared<ColorRGB>(0, 0, 0));
                        ptr2->normalize(width,height);
                        ptr2->render();
                        break;
                    }
                    case 1:{
                        std::shared_ptr<PixelMap> ptr = std::make_shared<PixelMap>(20 + 52 * i, 20 + 52 * j, 48, 48, std::make_shared<ColorRGB>(0, 0, 0));
                        baiLoader->colorVectorToPixelMap(baicolorVector, ptr);
                        ptr->normalize(width,height);
                        ptr->render();

                        std::shared_ptr<PixelMap> ptr2 = std::make_shared<PixelMap>(1050+10* i, 10* j, 10, 10, std::make_shared<ColorRGB>(255, 255, 255));
                        ptr2->normalize(width,height);
                        ptr2->render();
                        break;
                    }
                }
            }
        }
    }




    void Go::kill(){
        for(int i = 0;i < 19; i++){
            for(int j = 0;j < 19; j++){
                if(map[i][j] == 0)
                    continue;
                else{
                    block = new int[361];
                    blockLength = 1;
                    block[0] = i*100 + j;

                    recursion(i,j);

                    if(hasQi())
                        continue;
                    else {
                        for(int t = 0;t < blockLength; t++)
                            map[block[t]/100][block[t]%100] = 0;
                    }
                }
            }
        }
    }

    void Go::recursion(int i,int j){
        //Left
        if(i-1 >= 0 && map[i-1][j] == map[i][j] && isInBlock((i-1)*100+j)){
            block[blockLength] = (i-1)*100 + j;
            blockLength++;
            recursion(i-1,j);
        }
        //Up
        if(j-1 >= 0 && map[i][j-1] == map[i][j] && isInBlock(i*100+j-1)){
            block[blockLength] = i*100 + j-1;
            blockLength++;
            recursion(i,j-1);
        }
        //Right
        if(i+1 < 19 && map[i+1][j] == map[i][j] && isInBlock((i+1)*100+j)){
            block[blockLength] = (i+1)*100 + j;
            blockLength++;
            recursion(i+1,j);
        }
        //Down
        if(j+1 < 19 && map[i][j+1] == map[i][j] && isInBlock(i*100+j+1)){
            block[blockLength] = i*100 + j+1;
            blockLength++;
            recursion(i,j+1);
        }
    }

    bool Go::hasQi(){
        int i,j;
        for(int t = 0;t < blockLength; t++){
            i = block[t]/100;
            j = block[t]%100;
            if(i-1 >= 0 && map[i-1][j] == 0) return true;
            if(i+1 < 19 && map[i+1][j] == 0) return true;
            if(j-1 >= 0 && map[i][j-1] == 0) return true;
            if(j+1 < 19 && map[i][j+1] == 0) return true;
        }
        return false;
    }

    bool Go::isInBlock(int neighbor){
        for(int i = 0;i < blockLength; i++)
        {
            if (block[i] == neighbor) return false;
        }
        return true;
    }
    void Go::update() {
        qipan->normalize(width,height);
        qipan->render();
        RenderQiPan();
    }

    void Go::renderFPS() {
    }

    void Go::renderSysInfo() {
    }

    void Go::Render() {
            update();
    }

    int Go::run() {
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


        glfwSetKeyCallback(win, StateBase::keycallback_dispatch);
        glfwSetMouseButtonCallback(win, StateBase::mouse_button_callback_dispatch);
        glfwSetCursorPosCallback(win, StateBase::cursor_position_callback_dispatch);
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

