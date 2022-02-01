//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Tickables/Indicators/SMA.h"
#include "../Helpers/graph.h"
#include "IndicatorBaseNode.h"

class SMANode: public IndicatorBaseNode {
public:
    SMANode(std::shared_ptr<Indicator> sma,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
private:
};


#endif //BROKERAPP_SMANODE_H
