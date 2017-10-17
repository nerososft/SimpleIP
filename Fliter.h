//
// Created by neroyang on 2017/10/17.
//

#ifndef GP_HW_02_FLITER_H
#define GP_HW_02_FLITER_H

#include <vector>
#include "Pixel.h"
#include "PixelMap.h"

namespace OpenIP {

    class Fliter {

    private:
        PixelMap* pixelMap;
    public:
        Fliter(PixelMap *pixelMap);

        void min();
        void max();
        void median();
        void arithmetic_mean();
        void geometric_mean();

        void harmonics();
        void inverse_harmonic();

        PixelMap *getPixelMap() const;

        void setPixelMap(PixelMap *pixelMap);

    };
}


#endif //GP_HW_02_FLITER_H
