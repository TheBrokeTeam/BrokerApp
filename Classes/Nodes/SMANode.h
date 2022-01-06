//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/SMA.h"
#include "../Helpers/graph.h"

class SMANode: public INode {
public:
    SMANode(SMA* sma,std::shared_ptr<graph::Graph<GraphNode>> graph);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle()override ;

private:
    std::shared_ptr<SMA> _sma;
    std::shared_ptr<graph::Graph<GraphNode>> _graph;
};


#endif //BROKERAPP_SMANODE_H
