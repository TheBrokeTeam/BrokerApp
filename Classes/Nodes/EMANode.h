//
// Created by Luiz Veloso on 21/01/22.
//

#ifndef BROKERAPP_EMANODE_H
#define BROKERAPP_EMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/EMA.h"
#include "../Helpers/graph.h"

class EMANode: public INode {
public:
    EMANode(std::shared_ptr<Indicator> ema,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle() override;
private:
};


#endif //BROKERAPP_EMANODE_H
