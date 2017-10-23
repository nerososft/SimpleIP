//
// Created by neroyang on 2017/10/20.
//

#include "Segmentation.h"
#include <math.h>
#include <iostream>

namespace OpenIP{

    Segmentation::Segmentation(std::shared_ptr<PixelMap> pixelMap) : pixelMap(pixelMap) {

    }

    std::shared_ptr<PixelMap> Segmentation::convolution() {
        double op_x_matrix[3][3];

        double op_y_matrix[3][3];

        int size_operator = 3;

        switch (this->optr){
            case OPERATOR::Sobel: {
                double sobel_x_matrix[3][3] = {
                        {-1, -2, -1},
                        {0,  0,  0},
                        {1,  2,  1}
                };
                memcpy(op_x_matrix, sobel_x_matrix, sizeof(sobel_x_matrix));

                double sobel_y_matrix[3][3] = {
                        {-1, 0, 1},
                        {-2, 0, 2},
                        {-1, 0, 1}
                };
                memcpy(op_y_matrix, sobel_y_matrix, sizeof(sobel_y_matrix));
                size_operator = 3;
                break;
            }
            case OPERATOR::Prewitt: {
                double prewitt_x_matrix[3][3] = {
                        {-1, -1, -1},
                        {0,  0,  0},
                        {1,  1,  1}
                };
                memcpy(op_x_matrix, prewitt_x_matrix, sizeof(prewitt_x_matrix));

                double prewitt_y_matrix[3][3] = {
                        {-1, 0, 1},
                        {-1, 0, 1},
                        {-1, 0, 1}
                };
                memcpy(op_y_matrix, prewitt_y_matrix, sizeof(prewitt_y_matrix));
                size_operator = 3;
                break;
            }
            case OPERATOR::Roberts: {
                double roberts_x_matrix[2][2] = {
                        {-1, 0},
                        {0,  1}
                };
                memcpy(op_x_matrix, roberts_x_matrix, sizeof(roberts_x_matrix));

                double roberts_y_matrix[2][2] = {
                        {0, -1},
                        {1, 0}
                };
                memcpy(op_y_matrix, roberts_y_matrix, sizeof(roberts_y_matrix));
                size_operator = 2;
                break;
            }
            default: {
                double default_x_matrix[3][3] = {
                        {-1, -2, -1},
                        {0,  0,  0},
                        {1,  2,  1}
                };
                memcpy(op_x_matrix, default_x_matrix, sizeof(default_x_matrix));

                double default_y_matrix[3][3] = {
                        {-1, 0, 1},
                        {-2, 0, 2},
                        {-1, 0, 1}
                };
                memcpy(op_y_matrix, default_y_matrix, sizeof(default_y_matrix));
                size_operator = 3;
                break;
            }
        }

        std::vector<std::vector<std::shared_ptr<Pixel>>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    double Gx = 0;
                    double Gy = 0;
                    for (int r = -1; r < size_operator-1; r++) {
                        for (int c = -1; c < size_operator-1; c++) {
                            Gx+=tmp[i+r][j+c]->getColor()->R()*op_x_matrix[r+1][c+1];
                            Gy+=tmp[i+r][j+c]->getColor()->R()*op_y_matrix[r+1][c+1];
                        }
                    }
                    if((abs(Gx)+abs(Gy)) > this->distanceThreshold){
                        pixelMap->changeColor(i,j,std::make_shared<ColorRGB>((abs(Gx)+abs(Gy))*255,(abs(Gx)+abs(Gy))*255,(abs(Gx)+abs(Gy))*255));
                    }else{
                        pixelMap->changeColor(i,j,std::make_shared<ColorRGB>((0)*255,(0)*255,(0)*255));
                    };
                }else{
                    pixelMap->changeColor(i,j,std::make_shared<ColorRGB>((0)*255,(0)*255,(0)*255));
                }
            }
        }
        return this->getPixelMap();
    }

    std::shared_ptr<PixelMap> Segmentation::beelineFitting(){
        // A=∑xi^2,B=∑xi,C=∑yixi,D=∑yi
        std::shared_ptr<Line> line;
        switch(this->methodType){
            case FUNC::LSF: {
                line = this->lsfFuncFitLine(this->pixelMap);
                break;
            }
            case FUNC::RANSAC: {
                line = this->ransacFuncFitLine(this->pixelMap);
                break;
            }
            case FUNC::HOUGH: {
                line = this->houghFuncFitLine(this->pixelMap);
                break;
            }
            default: {
                break;
            }
        }
        std::cout<<"k: "<<line->getK()<<std::endl;
        std::cout<<"b: "<<line->getB()<<std::endl;
        for(int i  = 0;i<this->pixelMap->getWidth();i++){
            std::cout<<"x:"<<i<<" y:"<<(line->getK() * i + line->getB())<<std::endl;
            if((line->getK() * i + line->getB())>0 && (line->getK() * i + line->getB())<pixelMap->getHeight()) {
                pixelMap->changeColor(i, (line->getK() * i + line->getB()), this->lineColor);
            }
        }
        return this->getPixelMap();
    }

    std::shared_ptr<Line> Segmentation::lsfFuncFitLine(std::shared_ptr<PixelMap> pixelMap){
        std::vector<std::vector<std::shared_ptr<Pixel>>> tmp = this->pixelMap->getPixelMap();

        int A=0,B=0,C=0,D=0,N=0;
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if(tmp[i][j]->getColor()->R()==1){
                    A+=pow(i,2);
                    B+=i;
                    C+=i*j;
                    D+=j;
                    N++;
                }
            }
        }

        long double k=0,b=0,tmp1 =0;
//        k = ((A*D)-(B*C))/(N*A-pow(B,2));
//        b = (N*C-B*D)/(N*A-pow(B,2));
        if(tmp1=(A*N-B*B))
        {
            k = (C*N-B*D)/tmp1;
            b = (A*D-C*B)/tmp1;
        }
        else
        {
            k=1;
            b=0;
        }

        return std::make_shared<Line>(k,b);
    }

    std::shared_ptr<Line> Segmentation::ransacFuncFitLine(std::shared_ptr<PixelMap> pixelMap){

    }

    std::shared_ptr<Line> Segmentation::houghFuncFitLine(std::shared_ptr<PixelMap> pixelMap){
        std::vector<std::vector<std::shared_ptr<Pixel>>> tmp = this->pixelMap->getPixelMap();
        int *pArray;
        int iRMax = (int)sqrt(pow(pixelMap->getWidth(),2)  + pow(pixelMap->getHeight(),2)) + 1;
        int iThMax = 361;
        int iTh = 0;
        int iR;
        int iMax = -1;
        int iThMaxIndex = -1;
        int iRMaxIndex = -1;

        float pR;
        float pTh;

        pArray = new int[iRMax * iThMax];
        memset(pArray, 0, sizeof(int) * iRMax * iThMax);

        float fRate = (float)(PI/180);

        for (int y = 0; y < pixelMap->getHeight(); y++)
        {
            for (int x = 0; x < pixelMap->getWidth(); x++)
            {
                if(tmp[x][y]->getColor()->R() == 1)
                {
                    for(iTh = 0; iTh < iThMax; iTh += 1)
                    {
                        iR = (int)(x * cos(iTh * fRate) + y * sin(iTh * fRate));

                        if(iR > 0)
                        {
                            pArray[iR/1 * iThMax + iTh]++;
                        }
                    }
                }

            } // x
        } // y

        for(iR = 0; iR < iRMax; iR++)
        {
            for(iTh = 0; iTh < iThMax; iTh++)
            {
                int iCount = pArray[iR * iThMax + iTh];
                if(iCount > iMax)
                {
                    iMax = iCount;
                    iRMaxIndex = iR;
                    iThMaxIndex = iTh;
                }
            }
        }

        if(iMax >= this->distanceThreshold)
        {
            pR = iRMaxIndex;
            pTh = iThMaxIndex;
        }

        delete []pArray;

        std::cout<<"R "<<pR<<std::endl;
        std::cout<<"TH "<<pTh<<std::endl;


        float x = pR/cos(pTh>90?pTh-90:pTh);
        float y = pR/cos(90-pTh);
        std::cout<<"X "<<x<<std::endl;
        std::cout<<"Y "<<y<<std::endl;
        std::cout<<"Y/X "<<y/x<<std::endl;

        return std::make_shared<Line>(y/x,y);
    }

    std::shared_ptr<PixelMap> Segmentation::getPixelMap(){
        return pixelMap;
    }

    void Segmentation::setPixelMap(std::shared_ptr<PixelMap> pixelMap) {
        Segmentation::pixelMap = pixelMap;
    }

    OPERATOR Segmentation::getOptr() {
        return optr;
    }

    void Segmentation::setOptr(OPERATOR optr) {
        Segmentation::optr = optr;
    }

    FUNC Segmentation::getMethodType() const {
        return methodType;
    }

    void Segmentation::setMethodType(FUNC methodType) {
        Segmentation::methodType = methodType;
    }

    float Segmentation::getDistanceThreshold() const {
        return distanceThreshold;
    }

    void Segmentation::setDistanceThreshold(float distanceThreshold) {
        Segmentation::distanceThreshold = distanceThreshold;
    }

    const std::shared_ptr<ColorRGB> &Segmentation::getLineColor() const {
        return lineColor;
    }

    void Segmentation::setLineColor(const std::shared_ptr<ColorRGB> &lineColor) {
        Segmentation::lineColor = lineColor;
    }
}