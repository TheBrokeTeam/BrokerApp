//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_NODE_H
#define BROKERAPP_NODE_H

#include "INode.h"
template<typename InputT = int,typename OutputT = int>
class Node : public INode{
public:
    Node();
    virtual ~Node();
    virtual void onRender() override;

    virtual void setInput(int id, InputT value);
    virtual OutputT getOutput(int id);
    virtual OutputT getInput(int id);
};

template<typename InputT, typename OutputT>
Node<InputT, OutputT>::Node() {

}

template<typename InputT, typename OutputT>
Node<InputT, OutputT>::~Node() {

}

template<typename InputT, typename OutputT>
void Node<InputT, OutputT>::onRender() {
    INode::onRender();
}

template<typename InputT, typename OutputT>
void Node<InputT, OutputT>::setInput(int id, InputT value) {

}

template<typename InputT, typename OutputT>
OutputT Node<InputT, OutputT>::getOutput(int id) {
    return 0;
}

template<typename InputT, typename OutputT>
OutputT Node<InputT, OutputT>::getInput(int id) {
    return 0;
}


#endif //BROKERAPP_NODE_H
