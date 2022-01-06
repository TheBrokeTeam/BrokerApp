//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"
#include "../Tickables/Indicators/Indicator.h"

class SMANode: public INode {
public:
    SMANode(std::shared_ptr<Indicator> sma);
    void onRender(float dt) override;

    int _idOutput;
private:
    std::weak_ptr<Indicator> _indicator;
    IndicatorsView::CandleIndicatorsTypes _type = IndicatorsView::CandleIndicatorsTypes::SMA;
};


#endif //BROKERAPP_SMANODE_H
