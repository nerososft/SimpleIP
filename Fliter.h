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

        PixelMap* min();
        PixelMap* max();
        PixelMap* median();
        PixelMap* arithmetic_mean();
        PixelMap* geometric_mean();

        PixelMap* harmonics();
        PixelMap* inverse_harmonic();

        PixelMap *getPixelMap() const;

        void setPixelMap(PixelMap *pixelMap);

        virtual ~Fliter();

    };
}


#endif //GP_HW_02_FLITER_H
