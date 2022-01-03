//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "../Widgets/IndicatorsView.h"
#include "../Nodes/INode.h"

class SMANode: public INode {
public:
    SMANode();
    void onRender() override;

    int _idInput;
    int _idOutput;
    int _averageSize;

    IndicatorsView::CandleIndicatorsTypes _type = IndicatorsView::CandleIndicatorsTypes::SMA;
};


#endif //BROKERAPP_SMANODE_H
