//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "BaseNode.h"
#include "../IndicatorsView.h"


class SMANode: public BaseNode {
public:
    SMANode();
    void onRender() override;

    int _idInput;
    int _idOutput;
    int _averageSize;

    IndicatorsView::CandleIndicatorsTypes _type = IndicatorsView::CandleIndicatorsTypes::SMA;
};


#endif //BROKERAPP_SMANODE_H
