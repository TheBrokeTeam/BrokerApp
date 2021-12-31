//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CHARTVIEW_H
#define BROKERAPP_CHARTVIEW_H

#include "Widget.h"
#include "CandleChart.h"
#include <memory>

class ChartView : public Widget {
public:
    ChartView(Context* context);
    void updateVisible(float dt) override;
    void addChart(std::shared_ptr<CandleChart> candleChart);
    void enableIndicatorsOnCharts(bool show);
    void onPushStyleVar() override;

private:
    std::shared_ptr<CandleChart> _chart{nullptr};

};

#endif //BROKERAPP_CHARTVIEW_H
