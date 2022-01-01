//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#ifndef BROKERAPP_PROFITANDLOSSESVIEW_H
#define BROKERAPP_PROFITANDLOSSESVIEW_H

#include "Widget.h"
#include "../Tickables/Strategies/Strategy.h"
#include "../Tickables/Strategies/IndicatorFromChartExample.h"

class ProfitAndLossesView : public Widget {
public:
    ProfitAndLossesView(Context* context, Strategy* strategy);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

    void setStrategyTest(IndicatorFromChartExample* strategy);


private:
    Strategy* _strategy{nullptr};

};


#endif //BROKERAPP_PROFITANDLOSSESVIEW_H
