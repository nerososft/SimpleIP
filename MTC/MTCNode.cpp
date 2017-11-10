//
// Created by neroyang on 2017/11/1.
//

#include "MTCNode.h"
namespace OpenIP{
    template<class Node>
    void MTCNode<Node>::backpropagation() {

    }

    template<class Node>
    void MTCNode<Node>::expansion(std::shared_ptr<Action> action,std::shared_ptr<MTCNode> children) {
        childrens.insert(std::make_pair(action,children));
    }

    template<class Node>
    MTCNode<Node>::MTCNode(float weight, Node node, int count, const std::shared_ptr<MTCNode> &parent) : weight(weight), node(node), count(count), parent(parent) {

    }
}