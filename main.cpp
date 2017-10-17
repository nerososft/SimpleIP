
#include <freetype/ftglyph.h>
#include "ColorRGB.h"
#include "Board.hpp"
#include "Font.h"

int main(int argc, const char * argv[]) {
    OpenIP::Board* board = new OpenIP::Board("OpenIP",640,480,new OpenIP::ColorRGB(255,255,255));
    board->setEventHandling();
    board->run();


    return 0;
}
