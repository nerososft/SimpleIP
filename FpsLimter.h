//
// Created by neroyang on 2017/10/18.
//

#ifndef GP_HW_02_FPSLIMTER_H
#define GP_HW_02_FPSLIMTER_H

namespace OpenIP {
    class FpsLimter {
    public:
        FpsLimter();
        void init(float maxFPS);

        void setMaxFps(float maxFPS);

        void begin();

        float end();


    private:
        void calculateFPS();
        unsigned int _startTicks;

        float _maxFPS;
        float _fps;
        float _frameTime;

    };
}


#endif //GP_HW_02_FPSLIMTER_H
