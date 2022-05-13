//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_STRATEGYEDITOR_H
#define BROKERAPP_STRATEGYEDITOR_H

#include "Widget.h"
#include "../Tickables/Strategies/Strategy.h"
#include "../Nodes/INode.h"
#include "../Helpers/graph.h"
#include "NodesList.h"

class StrategyEditor : public Widget , public Tickable {
public:
    StrategyEditor(Ticker* ticker, Context* context);
    void onClose(BarHistory* barHistory) override;
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void addNode(std::shared_ptr<INode> newNode);
    void evaluateGraph(int id);
    void clear();

    const std::shared_ptr<graph::Graph<GraphNode>>& getGraph();

    void addRootId(int id);
    void removeRootId(int id);

    void removeNodeIndicator(std::shared_ptr<Indicator> indicator);

    std::vector<std::shared_ptr<INode>> getNodes();

    INode& addUiNode(NodeInfo nodeInfo);

    rapidjson::Document toJson();

    void fixNodesConnections(const std::vector<NodeInfo>& nodeInfo);

private:
    std::shared_ptr<INode> getNodeFromId(int id);
    void deleteUiNodeFromFromList(int id, bool shouldRemoveIndicator = true);
    std::vector<int> _rootNodes;
    std::shared_ptr<graph::Graph<GraphNode>> _graph{nullptr};
    std::vector<std::shared_ptr<INode>> _uiNodes;
    std::unique_ptr<NodesList> _nodesList{nullptr};

    ImGuiListClipper _clipper;
};

#endif //BROKERAPP_STRATEGYEDITOR_H
