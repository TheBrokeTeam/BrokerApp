//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_INDICATORTOCHARTEXAMPLE_H
#define BROKERAPP_INDICATORTOCHARTEXAMPLE_H

#include "Strategy.h"
#include "../Indicators/Bollinger.h"


class IndicatorToChartExample: public Strategy {
public:
    IndicatorToChartExample(Ticker* ticker);
    void rule() override;
    void checkTarget(Strategy::Position &pos) override;

private:
    double _targetPercent = 1.01;
    bool _isPositioned = false;
    Bollinger* _bollinger{nullptr};
};

#endif //BROKERAPP_INDICATORTOCHARTEXAMPLE_H
