//
// Created by Luiz Veloso on 04/03/22.
//

#include "VolumeData.h"

VolumeData::VolumeData(Ticker *ticker): IndicatorData(ticker) {

}

void VolumeData::calculate(BarHistory* barHistory)
{
    push((*barHistory)(0,BarDataType::VOLUME));
    _time.push_back((*barHistory)(0,BarDataType::TIME));
}