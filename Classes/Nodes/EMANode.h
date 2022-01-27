//
// Created by Luiz Veloso on 21/01/22.
//

#ifndef BROKERAPP_EMANODE_H
#define BROKERAPP_EMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/IndicatorBaseNode.h"
#include "../Tickables/Indicators/EMA.h"
#include "../Helpers/graph.h"

class EMANode: public IndicatorBaseNode {
public:
    EMANode(std::shared_ptr<Indicator> ema,StrategyEditor* nodeEditor);
    void handleStack(std::stack<float>& stack) override;
private:
};


#endif //BROKERAPP_EMANODE_H
