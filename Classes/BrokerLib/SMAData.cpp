//
// Created by Arthur Abel Motelevicz on 21/02/22.
//


#include "SMAData.h"
#include "../Tickers/Ticker.h"


SMAData::SMAData(Ticker *ticker): IndicatorData(ticker) {}

void SMAData::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += (*barHistory)(i,BarDataType::CLOSE);

        push(value / _averageSize);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }
}

void SMAData::setAverageSize(int size) {
    _averageSize = size;
}

int SMAData::getAverageSize() const {
    return _averageSize;
}



