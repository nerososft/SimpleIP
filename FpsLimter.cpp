//
// Created by neroyang on 2017/10/18.
//

#include <GLFW/glfw3.h>
#include <iostream>
#include "FpsLimter.h"
#include <stdio.h>
#include <sys/select.h>
namespace OpenIP{
    FpsLimter::FpsLimter(){

    }

    void FpsLimter::init(float maxFPS){
        setMaxFps(maxFPS);
    }

    void FpsLimter::setMaxFps(float maxFPS){
        _maxFPS = maxFPS;
    }

    void FpsLimter::begin(){
        _startTicks = glfwGetTime();
    }


    static void sleep_ms(unsigned int secs)
    {
        struct timeval tval;
        tval.tv_sec=secs/1000;
        tval.tv_usec=(secs*1000)%1000000;
        select(0,NULL,NULL,NULL,&tval);
    }

    float FpsLimter::end(){
        calculateFPS();
        float frameTicks = glfwGetTime() - _startTicks;

        if (1000.0f / _maxFPS>frameTicks){
            sleep_ms(1000.0f / _maxFPS - frameTicks);
        }

        return _fps;
    }


    void FpsLimter::calculateFPS(){

        static const int NUM_SAMPLES = 10;
        static float frameTimes[NUM_SAMPLES];
        static int currentFrame = 0;
        static float prevTicks = glfwGetTime();
        float currentTicks;
        currentTicks = glfwGetTime();

        _frameTime = currentTicks - prevTicks;
        frameTimes[currentFrame % NUM_SAMPLES] = _frameTime;

        prevTicks = currentTicks;
        int count;
        currentFrame++;
        if (currentFrame<NUM_SAMPLES){
            count = currentFrame;
        }
        else{
            count = NUM_SAMPLES;
        }

        float frameTimeAverage = 0;
        for (int i = 0; i < count; i++){
            frameTimeAverage += frameTimes[i];
        }
        frameTimeAverage /= count;

        if (frameTimeAverage>0){
            _fps = 1000.0f / frameTimeAverage;
        }
        else{
            _fps = 60.0f;
        }
    }
}