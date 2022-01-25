//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#ifndef BROKERAPP_BOLLINGERNODE_H
#define BROKERAPP_BOLLINGERNODE_H


#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/SMA.h"
#include "../Helpers/graph.h"

class BollingerNode: public INode {
public:
    BollingerNode(std::shared_ptr<Indicator> bollinger,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle()override ;
private:
    int _radioBtn = 1;
};


#endif //BROKERAPP_BOLLINGERNODE_H
