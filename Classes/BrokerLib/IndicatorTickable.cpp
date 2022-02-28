//
// Created by Arthur Abel Motelevicz on 21/02/22.
//


#include "IndicatorTickable.h"
#include "../Tickers/Ticker.h"

IndicatorTickable::IndicatorTickable(Ticker *ticker) : Tickable(ticker) {}

IndicatorTickable::~IndicatorTickable() = default;

void IndicatorTickable::onClose(BarHistory* barHistory)
{
    Tickable::onClose(barHistory);
    calculate(barHistory);
}

void IndicatorTickable::onLoad(BarHistory *barHistory)
{
    auto tempBarHist = std::make_unique<BarHistory>();
    for(int i = 0; i < barHistory->size(); i++){
        auto d = barHistory->getBarDataAt(i);
        tempBarHist->append(d);
        calculate(tempBarHist.get());
    }
}

void IndicatorTickable::reset()
{
    Tickable::reset();
    _time.clear();
}

Ticker *IndicatorTickable::getTicker() {
    return _ticker;
}



