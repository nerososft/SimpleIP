//
// Created by neroyang on 2017/10/23.
//

#ifndef GP_HW_02_LINE_H
#define GP_HW_02_LINE_H

#include <ostream>

namespace OpenIP {
    class Line {
    private:
        float k;
        float b;
    public:
        Line(float k, float b);

        float getK() const;

        void setK(float k);

        float getB() const;

        void setB(float b);

        friend std::ostream &operator<<(std::ostream &os, const Line &line);
    };
}


#endif //GP_HW_02_LINE_H
