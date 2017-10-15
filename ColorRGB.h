//
// Created by neroyang on 2017/10/14.
//

#ifndef GP_HW_02_COLORRGB_H
#define GP_HW_02_COLORRGB_H


#include <ostream>

class ColorRGB {
    private:
        unsigned int r;
        unsigned int g;
        unsigned int b;
public:
    ColorRGB(unsigned int r, unsigned int g, unsigned int b);

    float R(){return r/255.0f;};
    float G(){return g/255.0f;};
    float B(){return b/255.0f;}


    bool operator<(const ColorRGB &rhs) const;

    bool operator>(const ColorRGB &rhs) const;

    bool operator<=(const ColorRGB &rhs) const;

    bool operator>=(const ColorRGB &rhs) const;

    bool operator==(const ColorRGB &rhs) const;

    bool operator!=(const ColorRGB &rhs) const;

    friend std::ostream &operator<<(std::ostream &os, const ColorRGB &rgb);
};


#endif //GP_HW_02_COLORRGB_H
