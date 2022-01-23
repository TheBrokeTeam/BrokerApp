//
// Created by Luiz Veloso on 23/01/22.
//

#ifndef BROKERAPP_BASENODE_H
#define BROKERAPP_BASENODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Helpers/graph.h"

class BaseNode: public INode {
public:
    BaseNode(std::shared_ptr<Indicator> ind,StrategyEditor* nodeEditor);
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void initStyle() override;
    void finishStyle() override;
private:
};


#endif //BROKERAPP_BASENODE_H
