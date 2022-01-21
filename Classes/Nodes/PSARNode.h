//
// Created by Luiz Veloso on 21/01/22.
//

#ifndef BROKERAPP_PSARNODE_H
#define BROKERAPP_PSARNODE_H


#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/PSAR.h"
#include "../Helpers/graph.h"

class PSARNode: public INode {
public:
    PSARNode(std::shared_ptr<Indicator> psar,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle() override;
private:
};


#endif //BROKERAPP_PSARNODE_H