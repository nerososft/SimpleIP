//
// Created by neroyang on 2017/10/19.
//

#ifndef GP_HW_02_RANDOMPOLICYITERATION_H
#define GP_HW_02_RANDOMPOLICYITERATION_H


#include <vector>
#include <string>
#include "Action.h"
#include "TerminalState.h"

class RandomPolicyIteration {
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

    std::vector<std::shared_ptr<TerminalState>> terminalStates;

public:
    RandomPolicyIteration(double factor, double pi, double stepCost,int width, int height);

    void addTerminalState(std::shared_ptr<TerminalState> terminalState);

    double doAction(int x,int y,std::shared_ptr<Action> action);

    double doAllAction(int x,int y);

    bool checkOver();

    std::vector<std::vector<double>> train();
};


#endif //GP_HW_02_RANDOMPOLICYITERATION_H
