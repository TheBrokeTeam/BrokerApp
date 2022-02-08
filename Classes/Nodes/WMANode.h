//
// Created by Luiz Veloso on 21/01/22.
//

#ifndef BROKERAPP_WMANODE_H
#define BROKERAPP_WMANODE_H


#include "../Widgets/IndicatorsView.h"
#include "IndicatorBaseNode.h"
#include "../Tickables/Indicators/WMA.h"
#include "../Helpers/graph.h"

class WMANode: public IndicatorBaseNode {
public:
    WMANode(std::shared_ptr<Indicator> wma,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
private:
};

#endif //BROKERAPP_WMANODE_H
