//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/Indicator.h"
#include "../Helpers/graph.h"

class SMANode: public INode {
public:
    SMANode(std::shared_ptr<Indicator> sma,std::shared_ptr<graph::Graph<GraphNode>> graph);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

private:
    std::weak_ptr<Indicator> _indicator;
    std::shared_ptr<graph::Graph<GraphNode>> _graph;
};


#endif //BROKERAPP_SMANODE_H
