//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_STRATEGYEDITOR_H
#define BROKERAPP_STRATEGYEDITOR_H

#include "../Widget.h"
#include "../../Tickables/Strategies/Strategy.h"
#include "../../Nodes/INode.h"
#include "../../Nodes/GraphNode.h"
#include "../../Helpers/graph.h"

class StrategyEditor : public Widget {
public:
    explicit StrategyEditor(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void addNode(std::shared_ptr<INode> node);
    void removeNode(std::shared_ptr<INode> newNode);
    void evaluateGraph(int id);
    void clear();

    std::vector<std::weak_ptr<INode>> _nodes;
    std::vector<std::pair<int, int>> links;

    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    std::vector<std::shared_ptr<UiNode>> _uiNodes;
    void addRootId(int id);
    void removeRootId(int id);


private:
    INode* getNodeFromLinkId(int id);
    std::vector<int> _rootNodes;
};

#endif //BROKERAPP_STRATEGYEDITOR_H
