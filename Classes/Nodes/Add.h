//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#ifndef BROKERAPP_ADD_H
#define BROKERAPP_ADD_H

#include <memory>
#include "GraphNode.h"
#include "../Helpers/graph.h"
#include "INode.h"


class Add : public UiNode, public INode {
public:
    Add(std::shared_ptr<graph::Graph<GraphNode>> _graph);
    ~Add();
    void onRender(float dt) override;
    int idInput1;
    int idInput2;

private:
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};

};


#endif //BROKERAPP_ADD_H
