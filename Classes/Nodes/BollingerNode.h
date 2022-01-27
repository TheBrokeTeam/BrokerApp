//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#ifndef BROKERAPP_BOLLINGERNODE_H
#define BROKERAPP_BOLLINGERNODE_H


#include "../Widgets/IndicatorsView.h"
#include "../Nodes/IndicatorBaseNode.h"
#include "../Tickables/Indicators/SMA.h"
#include "../Helpers/graph.h"

class BollingerNode: public IndicatorBaseNode {
public:
    BollingerNode(std::shared_ptr<Indicator> bollinger,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
private:
    int _radioBtn = 1;
};


#endif //BROKERAPP_BOLLINGERNODE_H
