//
// Created by Luiz Veloso on 04/03/22.
//

#include "OHLCData.h"

OHLCData::OHLCData(Ticker *ticker): IndicatorData(ticker) {}

void OHLCData::calculate(BarHistory* barHistory)
{
    push((*barHistory)(0,BarDataType::OPEN), BarDataType::OPEN);
    push((*barHistory)(0,BarDataType::HIGH), BarDataType::HIGH);
    push((*barHistory)(0,BarDataType::LOW), BarDataType::LOW);
    push((*barHistory)(0,BarDataType::CLOSE), BarDataType::CLOSE);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
}