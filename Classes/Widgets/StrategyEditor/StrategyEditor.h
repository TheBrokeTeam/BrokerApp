//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_STRATEGYEDITOR_H
#define BROKERAPP_STRATEGYEDITOR_H

#include "../Widget.h"
#include "../../Tickables/Strategies/Strategy.h"
#include "../../Nodes/BaseNode.h"

class StrategyEditor : public Widget {
public:
    explicit StrategyEditor(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

    std::vector<std::weak_ptr<BaseNode>> _nodes;
    std::vector<std::pair<int, int>> links;

private:
    BaseNode* getNodeFromLinkId(int id);

};

#endif //BROKERAPP_STRATEGYEDITOR_H
