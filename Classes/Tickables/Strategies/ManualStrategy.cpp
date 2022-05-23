//
// Created by Arthur Abel Motelevicz on 27/03/22.
//

#include "ManualStrategy.h"

ManualStrategy::ManualStrategy(Ticker *ticker) : Strategy(ticker) {}

ManualStrategy::~ManualStrategy() {}

void ManualStrategy::resetPlot() {
    Strategy::resetPlot();
    isPositioned = false;
}