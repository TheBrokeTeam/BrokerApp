//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "IndicatorToChartExample.h"
#include "../../Contexts/Context.h"

IndicatorToChartExample::IndicatorToChartExample(Ticker *ticker) : Strategy(ticker) {
    setName("Strategy: Indicator to chart");

    _bollinger = dynamic_cast<Bollinger*>(ticker->getContext()->loadIndicator(IndicatorsView::CandleIndicatorsTypes::BOLL).get());

    if(_bollinger == nullptr)
        puts("ERROR creating bollinger indicator");
}

void IndicatorToChartExample::rule() {
    Strategy::rule();

    if(_isPositioned) return;

    if(barHist.size() < _bollinger->getAverageSize()) return;

    double lastPrice = barHist[0].close;
    double lastBollTop = (*_bollinger)[0].top;
    double lastBollBottom = (*_bollinger)[0].bottom;

    if( lastPrice > lastBollTop){
        auto id = openPosition(false);
        _isPositioned = true;
    }
    else if(lastPrice < lastBollBottom){
        auto id = openPosition(true);
        _isPositioned = true;
    }
}

void IndicatorToChartExample::checkTarget(Strategy::Position &pos) {
    Strategy::checkTarget(pos);

    double lastPrice = pos.outPrice;
    double deltaProfit = _targetPercent*pos.inPrice - pos.inPrice;
    double deltaLastPrice = pos.isShorting ? pos.inPrice - lastPrice : lastPrice - pos.inPrice;

    if( deltaLastPrice >= deltaProfit || deltaLastPrice <= -deltaProfit) {
        closePosition(pos.id);
        _isPositioned = false;
    }
}