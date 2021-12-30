//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#ifndef BROKERAPP_PROFITANDLOSSES_H
#define BROKERAPP_PROFITANDLOSSES_H

#include "Widget.h"
#include "../Tickables/Strategies/Strategy.h"
#include "../Tickables/Strategies/TestStrategy.h"

class ProfitAndLosses : public Widget {
public:
    ProfitAndLosses(Context* context, Strategy* strategy);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

    void setStrategyTest(TestStrategy* strategy);


private:
    Strategy* _strategy{nullptr};

};


#endif //BROKERAPP_PROFITANDLOSSES_H
