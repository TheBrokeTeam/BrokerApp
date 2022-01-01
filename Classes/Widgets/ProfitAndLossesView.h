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

private:
    std::weak_ptr<Strategy> _strategy;

};


#endif //BROKERAPP_PROFITANDLOSSESVIEW_H
