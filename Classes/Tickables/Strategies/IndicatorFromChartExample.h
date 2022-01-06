//
// Created by Arthur Abel Motelevicz on 29/12/21.
//

#ifndef BROKERAPP_INDICATORFROMCHARTEXAMPLE_H
#define BROKERAPP_INDICATORFROMCHARTEXAMPLE_H

#include "Strategy.h"
#include "../Indicators/SMA.h"


class IndicatorFromChartExample : public Strategy {
public:
    IndicatorFromChartExample(Ticker* ticker);
    void rule() override;
    void checkTarget(Strategy::Position &pos) override;

private:
    double _targetPercent = 1.01;
    bool _isPositioned = false;
};
#endif //BROKERAPP_INDICATORFROMCHARTEXAMPLE_H
