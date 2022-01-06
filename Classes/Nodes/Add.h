//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#ifndef BROKERAPP_ADD_H
#define BROKERAPP_ADD_H

#include <memory>
#include "../Helpers/graph.h"
#include "INode.h"

class Add : public INode{
public:
    Add(std::shared_ptr<graph::Graph<GraphNode>> _graph);
    ~Add();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

private:
    int _idInput1;
    int _idInput2;
};


#endif //BROKERAPP_ADD_H
