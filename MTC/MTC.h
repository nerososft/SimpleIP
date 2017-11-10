//
// Created by neroyang on 2017/11/1.
//

#ifndef GP_HW_02_MTC_H
#define GP_HW_02_MTC_H

#include <memory>
#include "MTCNode.h"

namespace OpenIP {
    template <class Node>
    class MTC {
    private:
        std::shared_ptr<MTCNode<Node>> top;
    public:
        void expansion();

        void simulation();

        void backpropagation();

    };
}


#endif //GP_HW_02_MTC_H
