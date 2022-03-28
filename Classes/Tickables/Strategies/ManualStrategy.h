//
// Created by Arthur Abel Motelevicz on 27/03/22.
//

#ifndef BROKERAPP_MANUALSTRATEGY_H
#define BROKERAPP_MANUALSTRATEGY_H

#include "Strategy.h"
class ManualStrategy : public Strategy {
public:
    inline static int current_count_id = 0;
    ManualStrategy(Ticker* ticker);
    ~ManualStrategy();
    void checkTarget(Strategy::Position &pos) override;
    void resetPlot() override;
    float takeProfitPrice = 0.0f;
    float stopLossPrice = 0.0f;
    bool isPositioned = false;
};

#endif //BROKERAPP_MANUALSTRATEGY_H
