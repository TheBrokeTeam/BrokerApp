//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#ifndef BROKERAPP_PROFITANDLOSSESVIEW_H
#define BROKERAPP_PROFITANDLOSSESVIEW_H

#include "Widget.h"
#include "../Tickables/Strategies/Strategy.h"

class ProfitAndLossesView : public Widget {
public:
    ProfitAndLossesView(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void setStrategyTest(std::weak_ptr<Strategy> strategy);
    void onClosePosition(const Strategy::Position& pos);
    void clear();

private:
    std::weak_ptr<Strategy> _strategy;
    std::vector<Strategy::Position> _closedPositions;
    std::vector<double> _plotTime;
    std::vector<double> _plotProfit;
    std::vector<double> _plotLosses;
    double _baseLine = 0;
    double _cumulatedProfit;
    double _lastTime;
    int _maxPositionsToRender = 1000;
};


#endif //BROKERAPP_PROFITANDLOSSESVIEW_H
