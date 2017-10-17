//
// Created by neroyang on 2017/10/17.
//

#include <iostream>
#include <cmath>
#include "Fliter.h"
#include "Math.h"

namespace OpenIP{


    Fliter::Fliter(PixelMap *pixelMap) : pixelMap(pixelMap) {}

    void Fliter::min() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();

        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float gray[9];
                    int index = 0;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            gray[index] = tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                          tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                          tmp[i + r][j + c]->getColor()->B() * 0.11f;
                            index++;
                        }
                    }

                    Math *math = new Math();
                    int len = sizeof(gray) / sizeof(int);
                    math->quickSort(gray, 0, len - 1);

                    float current_gray = gray[0];
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            if (current_gray == tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                                tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                                tmp[i + r][j + c]->getColor()->B() * 0.11f) {
                                this->pixelMap->changeColor(i, j, tmp[i + r][j + c]->getColor());
                            }
                        }
                    }
                }
            }
        }
    }

    void Fliter::max() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();

        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float gray[9];
                    int index = 0;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            gray[index] = tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                          tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                          tmp[i + r][j + c]->getColor()->B() * 0.11f;
                            index++;
                        }
                    }

                    Math *math = new Math();
                    int len = sizeof(gray) / sizeof(int);
                    math->quickSort(gray, 0, len - 1);

                    float current_gray = gray[8];
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            if (current_gray == tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                                tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                                tmp[i + r][j + c]->getColor()->B() * 0.11f) {
                                this->pixelMap->changeColor(i,j,tmp[i + r][j + c]->getColor());
                            }
                        }
                    }
                }
            }
        }
    }

    void Fliter::median() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();

        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float gray[9];
                    int index = 0;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            gray[index] = tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                          tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                          tmp[i + r][j + c]->getColor()->B() * 0.11f;
                            index++;
                        }
                    }

                    Math *math = new Math();
                    int len = sizeof(gray) / sizeof(int);
                    math->quickSort(gray, 0, len - 1);
                    float current_gray = gray[4]; //    灰度值中位数

                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            if (current_gray == tmp[i + r][j + c]->getColor()->R() * 0.03f +
                                                tmp[i + r][j + c]->getColor()->G() * 0.59f +
                                                tmp[i + r][j + c]->getColor()->B() * 0.11f) {

                               this->pixelMap->changeColor(i,j,tmp[i + r][j + c]->getColor());
                            }
                        }
                    }
                }
            }
        }

    }

    void Fliter::arithmetic_mean() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float R = 0.0f, G = 0.0f, B = 0.0f;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            R += tmp[i + r][j + c]->getColor()->R();
                            G += tmp[i + r][j + c]->getColor()->G();
                            B += tmp[i + r][j + c]->getColor()->B();
                        }
                    }
                    R = (R / 9.0f) * 255.0f;
                    G = (G / 9.0f) * 255.0f;
                    B = (B / 9.0f) * 255.0f;
                    this->pixelMap->changeColor(i,j,new ColorRGB(R, G, B));
                }
            }
        }
    }

    void Fliter::geometric_mean() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float R = 1.0f, G = 1.0f, B = 1.0f;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            R *= (tmp[i + r][j + c]->getColor()->R() * 255.0f);
                            G *= (tmp[i + r][j + c]->getColor()->G() * 255.0f);
                            B *= (tmp[i + r][j + c]->getColor()->B() * 255.0f);
                        }
                    }

                    R = pow(R, 1.0f / 9.0f);
                    G = pow(G, 1.0f / 9.0f);
                    B = pow(B, 1.0f / 9.0f);
                    this->pixelMap->changeColor(i,j,new ColorRGB(R, G, B));
                }
            }
        }
    }

    void Fliter::harmonics() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float R = 0.0f, G = 0.0f, B = 0.0f;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            R += (1.0f / tmp[i + r][j + c]->getColor()->R());
                            G += (1.0f / tmp[i + r][j + c]->getColor()->G());
                            B += (1.0f / tmp[i + r][j + c]->getColor()->B());
                        }
                    }
                    R = (9.0f / R) * 255.0f;
                    G = (9.0f / G) * 255.0f;
                    B = (9.0f / B) * 255.0f;
                    this->pixelMap->changeColor(i,j,new ColorRGB(R, G, B));
                }
            }
        }

    }

    void Fliter::inverse_harmonic() {
        std::vector<std::vector<Pixel*>> tmp = this->pixelMap->getPixelMap();
        for (int i = 0; i < this->pixelMap->getWidth(); i++) {
            for (int j = 0; j < this->pixelMap->getHeight(); j++) {
                if (i > 1 && i < this->pixelMap->getWidth() - 1 && j > 1 && j < this->pixelMap->getHeight() - 1) {
                    float R = 0.0f, G = 0.0f, B = 0.0f, R1 = 0.0f, G1 = 0.0f, B1 = 0.0f;
                    float Q = 0;
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            R += (pow(tmp[i + r][j + c]->getColor()->R(), Q));
                            G += (pow(tmp[i + r][j + c]->getColor()->G(), Q));
                            B += (pow(tmp[i + r][j + c]->getColor()->B(), Q));
                        }
                    }
                    for (int r = -1; r < 2; r++) {
                        for (int c = -1; c < 2; c++) {
                            R1 += (pow(tmp[i + r][j + c]->getColor()->R(), Q + 1.0f));
                            G1 += (pow(tmp[i + r][j + c]->getColor()->G(), Q + 1.0f));
                            B1 += (pow(tmp[i + r][j + c]->getColor()->B(), Q + 1.0f));
                        }
                    }
                    R = (R1 / R) * 255.0f;
                    G = (G1 / G) * 255.0f;
                    B = (B1 / B) * 255.0f;
                    this->pixelMap->changeColor(i,j,new ColorRGB(R, G, B));

                }
            }
        }
    }

    PixelMap *Fliter::getPixelMap() const {
        return pixelMap;
    }

    void Fliter::setPixelMap(PixelMap *pixelMap) {
        Fliter::pixelMap = pixelMap;
    }
}


