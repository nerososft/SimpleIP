//
// Created by neroyang on 2017/10/19.
//

#ifndef GP_HW_02_VALUEITERATION_H
#define GP_HW_02_VALUEITERATION_H


#include <vector>
#include "Action.h"

class ValueIteration {
private:
    double factor;
    double pi;
    double stepCost;
    double targetX;
    double targetY;
    double targetReword;

    int width;
    int height;

    std::vector<std::shared_ptr<Action>> actions;
    std::vector<std::vector<double>> cha;
    std::vector<std::vector<double>> rewords;

public:
    ValueIteration(double factor, double pi, double stepCost,int width, int height);

    void addPoint(int x,int y ,double targetValue);

    double doAction(int x,int y,std::shared_ptr<Action> action);

    double doAllAction(int x,int y);

    bool checkOver();

    std::vector<std::vector<double>> train();
};


#endif //GP_HW_02_VALUEITERATION_H
