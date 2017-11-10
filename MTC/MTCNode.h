//
// Created by neroyang on 2017/11/1.
//

#ifndef GP_HW_02_MTCNODE_H
#define GP_HW_02_MTCNODE_H

#include <vector>
#include <map>
#include "../rl/Action.h"

namespace OpenIP {
    template <class Node>
    class MTCNode {
    private:
        float weight;
        Node node;
        int count;
        std::map<std::shared_ptr<Action>,std::shared_ptr<MTCNode>> childrens;
        std::shared_ptr<MTCNode> parent;

    public:
        MTCNode(float weight, Node node, int count, const std::shared_ptr<MTCNode> &parent);

        void backpropagation();

        void expansion(std::shared_ptr<Action> action,std::shared_ptr<MTCNode> children);
    };
}


#endif //GP_HW_02_MTCNODE_H
