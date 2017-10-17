
#include "ColorRGB.h"
#include "Board.hpp"

int main(int argc, const char * argv[]) {
    OpenIP::Board* board = new OpenIP::Board("图像处理作业-滤波[边缘未处理]-杨兴锋-3015218102",640,480,new OpenIP::ColorRGB(255,255,255));
    board->setEventHandling();
    board->run();

    return 0;
}
