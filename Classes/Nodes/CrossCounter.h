//
// Created by Arthur Abel Motelevicz on 05/01/22.
//

#ifndef BROKERAPP_CROSSCOUNTER_H
#define BROKERAPP_CROSSCOUNTER_H

#include <memory>
#include "../Helpers/graph.h"
#include "INode.h"


class CrossCounter : public INode{
public:
    CrossCounter(std::shared_ptr<graph::Graph<GraphNode>> _graph);
    ~CrossCounter();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
private:
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    int _idInput;
    int _counter = 0;
};


#endif //BROKERAPP_CROSSCOUNTER_H
