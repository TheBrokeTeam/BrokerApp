//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_STRATEGYEDITOR_H
#define BROKERAPP_STRATEGYEDITOR_H

#include "../Widget.h"
#include "../../Tickables/Strategies/Strategy.h"
#include "TestNode.h"

class StrategyEditor : public Widget {
public:
    explicit StrategyEditor(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

    std::vector<TestNode> _nodes;
    std::vector<std::pair<int, int>> links;
private:

};

#endif //BROKERAPP_STRATEGYEDITOR_H
