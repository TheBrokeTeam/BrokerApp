//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CHART_H
#define BROKERAPP_CHART_H

#include "Widget.h"
#include "../Widget+Tickables/CandleChart.h"
#include <memory>

class Chart : public Widget {
public:
    Chart(Editor* editor);
    void updateVisible(float dt) override;
    void addChart(std::shared_ptr<CandleChart> candleChart);
    void enableIndicatorsOnCharts(bool show);
    void onPushStyleVar() override;

private:
    std::vector<std::shared_ptr<CandleChart>> _charts;

};

#endif //BROKERAPP_CHART_H
