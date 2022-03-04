//
// Created by Luiz Veloso on 04/03/22.
//

#include "OHLCData.h"

OHLCData::OHLCData(Ticker *ticker): IndicatorData(ticker) {}

void OHLCData::calculate(BarHistory* barHistory)
{
        push((*barHistory)(0,BarDataType::CLOSE));
        _time.push_back((*barHistory)(0,BarDataType::TIME));
}