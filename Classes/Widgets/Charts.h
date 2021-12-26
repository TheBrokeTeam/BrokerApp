//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CHARTS_H
#define BROKERAPP_CHARTS_H

#include "Widget.h"
#include "../Widget+Tickables/CandleChart.h"
#include <memory>

class Charts : public Widget {
public:
    Charts(Editor* editor);
    void updateVisible(float dt) override;
    void addChart(std::shared_ptr<CandleChart> candleChart);
    void enableIndicatorsOnCharts(bool show);
    void onPushStyleVar() override;

private:
    std::vector<std::shared_ptr<CandleChart>> _charts;

};

#endif //BROKERAPP_CHARTS_H
