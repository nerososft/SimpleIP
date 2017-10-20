
#include <freetype/ftglyph.h>
#include "ColorRGB.h"
#include "Board.hpp"
#include "Font.h"
#include "rl/mdp.h"

int main(int argc, const char * argv[]) {
    OpenIP::Board* board = new OpenIP::Board("OpenIP",640,480,std::make_shared<OpenIP::ColorRGB>(255,255,255));
    board->setEventHandling();
    board->run();
    return 0;
}
