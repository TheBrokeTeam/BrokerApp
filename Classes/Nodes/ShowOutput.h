//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#ifndef BROKERAPP_SHOWOUTPUT_H
#define BROKERAPP_SHOWOUTPUT_H

#include <memory>
#include "../Helpers/graph.h"
#include "INode.h"


class ShowOutput : public INode{
public:
    ShowOutput(std::shared_ptr<graph::Graph<GraphNode>> _graph);
    ~ShowOutput();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

    int getIdInput();
private:
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    int _idInput;
    float _value;
};



#endif //BROKERAPP_SHOWOUTPUT_H
