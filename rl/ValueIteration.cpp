//
// Created by neroyang on 2017/10/19.
//

#include "ValueIteration.h"
#include <iostream>
#include  <math.h>
#include "../Math.h"

double ValueIteration::doAction(int x, int y, std::shared_ptr<Action> action) {

    switch(action->getActionID()){
        case 1: //up
            if(y==0){ //
                return -1 + (1.0/actions.size())*factor*rewords[x][y];
            }else{
                return (1.0/actions.size())*factor*rewords[x][y-1];
            }
        case 2: //down
            if(y==height-1){ //
                return -1 +(1.0/actions.size())*factor*rewords[x][y];
            }else{
                return (1.0/actions.size())*factor*rewords[x][y+1];
            }
        case 3:  //left
            if(x==0){ //
                return -1 +(1.0/actions.size())*factor*rewords[x][y];
            }else{
                return (1.0/actions.size())*factor*rewords[x-1][y];
            }
        case 4: //right
            if(x==width-1){ //
                return -1 +(1.0/actions.size())*factor*rewords[x][y];
            }else{
                return (1.0/actions.size())*factor*rewords[x+1][y];
            }
    }
}

double ValueIteration::doAllAction(int x,int y){
    double rew = 0.0;
    double costActions[4];
    for(int a = 0;a<actions.size();a++){
        double actionCost = doAction(x,y,actions[a]); //动作花费
        costActions[a] = actionCost;
    }
    std::shared_ptr<OpenIP::Math> math = std::make_shared<OpenIP::Math>();
    int len = sizeof(costActions) / sizeof(double);
    math->quickSortDouble(costActions,0,len-1);
    rew += costActions[3];
    rew += stepCost; //一步花费
    cha[x][y] = rew-rewords[x][y];
    return rew;
}

bool ValueIteration::checkOver(){
    double max = 0;
    for(int i = 0;i<width;i++){
        for(int j = 0;j<height;j++){
            std::cout<< rewords[i][j] <<"  ";
            if(cha[i][j]>=max){
                max = cha[i][j];
            }
        }
        std::cout<<std::endl;
    }
    if(max<=pi){
        return true;
    }
    std::cout<<"--------------------------------------------"<<std::endl;
    return false;
}

std::vector<std::vector<double>> ValueIteration::train(){
    while(!checkOver()) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                rewords[i][j] = doAllAction(i, j);
            }
        }
    }
    return rewords;
}

void ValueIteration::addPoint(int x,int y ,double targetValue){
    rewords[x][y] = targetValue;
    cha[x][y] = targetValue;
}

ValueIteration::ValueIteration(double factor, double pi, double stepCost,  int width, int height) : factor(factor), pi(pi), stepCost(stepCost),  width(width),
                                                                                                                  height(height) {

    //初始化动作集合
    actions.push_back(std::make_shared<Action>(1,"up"));
    actions.push_back(std::make_shared<Action>(2,"down"));
    actions.push_back(std::make_shared<Action>(3,"left"));
    actions.push_back(std::make_shared<Action>(4,"right"));


    for(int i = 0;i<width;i++){
        std::vector<double> reword;
        std::vector<double> ch;
        for(int j = 0;j<height;j++){
            reword.push_back(0);
            ch.push_back(0);
        }
        rewords.push_back(reword);
        cha.push_back(ch);
    }
}
