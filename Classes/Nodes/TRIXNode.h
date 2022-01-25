//
// Created by Luiz Veloso on 21/01/22.
//

#ifndef BROKERAPP_TRIXNODE_H
#define BROKERAPP_TRIXNODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/TRIX.h"
#include "../Helpers/graph.h"

class TRIXNode: public INode {
public:
    TRIXNode(std::shared_ptr<Indicator> trix,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle() override;
private:
};


#endif //BROKERAPP_TRIXNODE_H
