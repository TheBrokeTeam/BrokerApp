//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#ifndef BROKERAPP_SHOWOUTPUT_H
#define BROKERAPP_SHOWOUTPUT_H

#include <memory>
#include "GraphNode.h"
#include "../Helpers/graph.h"
#include "INode.h"


class ShowOutput : public UiNode{
public:
    ShowOutput(std::shared_ptr<graph::Graph<GraphNode>> _graph);
    ~ShowOutput();
    void onRender(float dt) override;
    int getIdInput();
private:
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    int _idInput;
};



#endif //BROKERAPP_SHOWOUTPUT_H
