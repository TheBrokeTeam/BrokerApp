//
// Created by Arthur Abel Motelevicz on 21/02/22.
//


#include "IndicatorData.h"
#include "../Tickers/Ticker.h"

IndicatorData::IndicatorData(Ticker *ticker) : Tickable(ticker) {}

IndicatorData::~IndicatorData() = default;

void IndicatorData::onClose(BarHistory* barHistory)
{
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void IndicatorData::onLoad(BarHistory *barHistory)
{
    auto tempBarHist = std::make_unique<BarHistory>();
    for(int i = 0; i < barHistory->size(); i++){
        auto d = barHistory->getBarDataAt(i);
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}

void IndicatorData::reset()
{
    Tickable::reset();
    _time.clear();
}

Ticker *IndicatorData::getTicker() {
    return _ticker;
}



