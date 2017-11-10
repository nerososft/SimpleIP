
#include <freetype/ftglyph.h>
#include "ColorRGB.h"
#include "rl/ValueIteration.h"
#include "Go.h"


int main(int argc, const char * argv[]) {
    OpenIP::Go* go = new OpenIP::Go("OpenIP GO",768,512,std::make_shared<OpenIP::ColorRGB>(244,194,125));
    go->setEventHandling();
    go->run();
    return 0;
}
