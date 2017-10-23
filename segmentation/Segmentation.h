//
// Created by neroyang on 2017/10/20.
//

#ifndef GP_HW_02_SEGMENTATION_H
#define GP_HW_02_SEGMENTATION_H

#include <memory>
#include "../PixelMap.h"
#include "Line.h"

#define PI 3.14159265354

namespace  OpenIP {
    enum OPERATOR{
        Sobel,Roberts,Prewitt
    };
    enum FUNC{
        LSF,RANSAC,HOUGH
    };

    class Segmentation {
    private:
        std::shared_ptr<PixelMap> pixelMap;
        OPERATOR  optr;
        FUNC methodType;
        float distanceThreshold = 0;
        std::shared_ptr<ColorRGB> lineColor;

    public:

        Segmentation(std::shared_ptr<PixelMap> pixelMap);

        std::shared_ptr<PixelMap> convolution();

        std::shared_ptr<PixelMap> beelineFitting();

        std::shared_ptr<PixelMap> getPixelMap();

        std::shared_ptr<Line> lsfFuncFitLine(std::shared_ptr<PixelMap> pixelMap);//最小二乘拟合直线

        std::shared_ptr<Line> ransacFuncFitLine(std::shared_ptr<PixelMap> pixelMap);//ransac拟合直线

        std::shared_ptr<Line> houghFuncFitLine(std::shared_ptr<PixelMap> pixelMap);//hough拟合直线

        void setPixelMap(std::shared_ptr<PixelMap> pixelMap);

        OPERATOR getOptr();

        void setOptr(OPERATOR optr);

        FUNC getMethodType() const;

        void setMethodType(FUNC methodType);

        float getDistanceThreshold() const;

        void setDistanceThreshold(float distanceThreshold);

        const std::shared_ptr<ColorRGB> &getLineColor() const;

        void setLineColor(const std::shared_ptr<ColorRGB> &lineColor);
    };
}


#endif //GP_HW_02_SEGMENTATION_H
