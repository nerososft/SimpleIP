
#include <freetype/ftglyph.h>
#include "ColorRGB.h"
#include "Board.hpp"
#include "rl/ValueIteration.h"


int main(int argc, const char * argv[]) {
    OpenIP::Board* board = new OpenIP::Board("Segmentation",640,480,std::make_shared<OpenIP::ColorRGB>(255,255,255));
    board->setEventHandling();
    board->run();
    return 0;

//    ValueIteration* iteration = new  ValueIteration(0.9, 1, -1,10, 10);
//    iteration->addPoint(5,5,100);
//    std::vector<std::vector<double>> rewords = iteration->train();
//
//    for(int i = 0;i<10;i++){
//        for(int j = 0;j<10;j++){
//            std::cout<<rewords[i][j]<<"    ";
//        }
//        std::cout<<std::endl;
//    }



}
