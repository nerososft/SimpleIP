//
// Created by neroyang on 2017/10/20.
//

#include "Segmentation.h"
#include <math.h>
#include <iostream>

namespace OpenIP{

    Segmentation::Segmentation(std::shared_ptr<PixelMap> pixelMap) : pixelMap(pixelMap) {

    }


    std::shared_ptr<PixelMap> Segmentation::convolution(OPERATOR op,float yuzhi) {

            double op_x_matrix[3][3] = {
                    {-1,-2,-1},
                    {0,0,0},
                    {1,2,1}
            };
            double op_y_matrix[3][3] = {
                {-1,0,1},
                {-2,0,2},
                {-1,0,1}
            };

        std::vector<std::vector<std::shared_ptr<Pixel>>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    double Gx = 0;
                    double Gy = 0;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            Gx+=tmp[i+r][j+c]->getColor()->R()*op_x_matrix[r+1][c+1];
                            Gy+=tmp[i+r][j+c]->getColor()->R()*op_y_matrix[r+1][c+1];
                        }
                    }
                    if((abs(Gx)+abs(Gy)) > yuzhi){
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

    std::shared_ptr<PixelMap> Segmentation::beelineFitting(std::shared_ptr<ColorRGB> color){
        // A=∑xi^2,B=∑xi,C=∑yixi,D=∑yi
        // Ak+Bb=C
        // Bk+nb=D
        std::vector<std::vector<std::shared_ptr<Pixel>>> tmp = this->pixelMap->getPixelMap();
        int A=0,B=0,C=0,D=0;
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if(tmp[i][j]->getColor()->R()>=200){
                    A+=pow(i,2);
                    B+=i;
                    C+=i*j;
                    D+=j;
                    //count
                }
            }
        }
        double k=0,b=0,tmp1 =0;

        if(tmp1=(A*this->pixelMap->getWidth()-B*B))
        {
            k = (C*this->pixelMap->getWidth()-B*D)/tmp1;
            b = (A*D-C*B)/tmp1;
        }
        else
        {
            k=1;
            b=0;
        }

        std::cout<<"k: "<<k<<std::endl;
        std::cout<<"b: "<<b<<std::endl;
        for(int i  = 0;i<this->pixelMap->getWidth();i++){
            std::cout<<"x:"<<i<<" y:"<<floor(k * i + b)<<std::endl;
            if(floor(k * i + b)>0 && floor(k * i + b)<pixelMap->getHeight()) {
                pixelMap->changeColor(i, floor(k * i + b), color);
            }
        }

        return this->getPixelMap();
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
}