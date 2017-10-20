//
// Created by neroyang on 2017/10/20.
//

#ifndef GP_HW_02_SEGMENTATION_H
#define GP_HW_02_SEGMENTATION_H

#include <memory>
#include "../PixelMap.h"

namespace  OpenIP {
    enum OPERATOR{
        Sobel,Roberts,Prewitt
    };

    class Segmentation {
    private:
        std::shared_ptr<PixelMap> pixelMap;
        OPERATOR  optr;
    public:

        Segmentation(std::shared_ptr<PixelMap> pixelMap);

        std::shared_ptr<PixelMap> convolution(OPERATOR op,float yuzhi);

        std::shared_ptr<PixelMap> beelineFitting(std::shared_ptr<ColorRGB> color);

        std::shared_ptr<PixelMap> getPixelMap();

        void setPixelMap(std::shared_ptr<PixelMap> pixelMap);

        OPERATOR getOptr();

        void setOptr(OPERATOR optr);
    };
}


#endif //GP_HW_02_SEGMENTATION_H
