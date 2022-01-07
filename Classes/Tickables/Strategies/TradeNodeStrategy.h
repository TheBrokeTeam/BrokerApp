//
// Created by Arthur Abel Motelevicz on 07/01/22.
//

#ifndef BROKERAPP_TRADENODESTRATEGY_H
#define BROKERAPP_TRADENODESTRATEGY_H

#include "Strategy.h"
class TradeNodeStrategy : public Strategy {
public:
    inline static int current_count_id = 0;
    TradeNodeStrategy(Ticker* ticker);
    ~TradeNodeStrategy();
    void checkTarget(Strategy::Position &pos) override;
    float takeProfit = 5.0f;    //0 - 100
    float stopLoss = 5.0f;      //0 - 100
    bool isPositioned = false;
};

#endif //BROKERAPP_TRADENODESTRATEGY_H
