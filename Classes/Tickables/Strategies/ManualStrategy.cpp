//
// Created by Arthur Abel Motelevicz on 27/03/22.
//

#include "ManualStrategy.h"

ManualStrategy::ManualStrategy(Ticker *ticker) : Strategy(ticker) {}

void ManualStrategy::checkTarget(Strategy::Position &pos) {
    Strategy::checkTarget(pos);

    double targetProfit = takeProfitPrice - pos.inPrice;
    double targetStopLoss = stopLossPrice - pos.inPrice;

    if( pos.profit >= targetProfit ||  pos.profit <= targetStopLoss) {
        closePosition(pos.id);
        isPositioned = false;
    }
}

ManualStrategy::~ManualStrategy() {}

void ManualStrategy::resetPlot() {
    Strategy::resetPlot();
    isPositioned = false;
}

