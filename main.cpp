
#include "Board.hpp"
#include "PNGLoader.h"

int main(int argc, const char * argv[]) {
    Board* board = new Board("图像处理作业-滤波[边缘未处理]-杨兴锋-3015218102",640,480,new ColorRGB(255,255,255));
    board->setEventHandling();
    board->run();


    return 0;
}