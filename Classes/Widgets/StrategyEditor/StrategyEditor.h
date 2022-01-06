//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_STRATEGYEDITOR_H
#define BROKERAPP_STRATEGYEDITOR_H

#include "../Widget.h"
#include "../../Tickables/Strategies/Strategy.h"
#include "../../Nodes/INode.h"
#include "../../Helpers/graph.h"

class StrategyEditor : public Widget {
public:
    explicit StrategyEditor(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void addNode(std::shared_ptr<INode> newNode);
    void removeNode(std::shared_ptr<INode> newNode);
    void evaluateGraph(int id);
    void clear();

    const std::shared_ptr<graph::Graph<GraphNode>>& getGraph();

    void addRootId(int id);
    void removeRootId(int id);


private:
    std::shared_ptr<INode> getNodeFromId(int id);
    void deleteUiNodeFromFromList(int id);
    std::vector<int> _rootNodes;
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    std::vector<std::shared_ptr<INode>> _uiNodes;
};

#endif //BROKERAPP_STRATEGYEDITOR_H
