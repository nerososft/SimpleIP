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
        std::shared_ptr<PixelMap> pixelMap;
    public:
        Fliter(std::shared_ptr<PixelMap> pixelMap);

        std::shared_ptr<PixelMap> min();
        std::shared_ptr<PixelMap> max();
        std::shared_ptr<PixelMap> median();
        std::shared_ptr<PixelMap> arithmetic_mean();
        std::shared_ptr<PixelMap> geometric_mean();

        std::shared_ptr<PixelMap> harmonics();
        std::shared_ptr<PixelMap> inverse_harmonic();

        std::shared_ptr<PixelMap> getPixelMap() const;

        void setPixelMap(std::shared_ptr<PixelMap> pixelMap);

        virtual ~Fliter();

    };
}


#endif //GP_HW_02_FLITER_H
