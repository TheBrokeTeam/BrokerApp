//
// Created by Arthur Abel Motelevicz on 07/01/22.
//

#include "TradeNodeStrategy.h"

TradeNodeStrategy::TradeNodeStrategy(Ticker *ticker) : Strategy(ticker) {}

void TradeNodeStrategy::checkTarget(Strategy::Position &pos) {
    Strategy::checkTarget(pos);
    double targetProfit = (takeProfit/100.0f)*pos.inPrice;
    double targetStopLoss = (stopLoss/100.0f)*pos.inPrice*(-1.0);

    if( pos.profit >= targetProfit ||  pos.profit <= targetStopLoss) {
        closePosition(pos.id);
        isPositioned = false;
    }
}

TradeNodeStrategy::~TradeNodeStrategy() {}

void TradeNodeStrategy::resetPlot() {
    Strategy::resetPlot();
    isPositioned = false;
}

