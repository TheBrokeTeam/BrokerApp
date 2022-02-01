//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#ifndef BROKERAPP_VWAPNODE_H
#define BROKERAPP_VWAPNODE_H


#include "../Widgets/IndicatorsView.h"
#include "IndicatorBaseNode.h"
#include "../Tickables/Indicators/VWAP.h"
#include "../Helpers/graph.h"

class VWAPNode: public IndicatorBaseNode {
public:
    VWAPNode(std::shared_ptr<Indicator> vwap,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
private:
};



#endif //BROKERAPP_VWAPNODE_H
