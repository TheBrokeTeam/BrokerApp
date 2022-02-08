//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CHARTVIEW_H
#define BROKERAPP_CHARTVIEW_H

#include "Widget.h"
#include "CandleChart.h"
#include "LiveCandleChart.h"

#include <memory>

class ChartView : public Widget {
public:
    ChartView(Context* context);
    void updateVisible(float dt) override;
    void addChart(std::shared_ptr<CandleChart> candleChart);
    //temp need will be removed
    void addLiveChart(std::shared_ptr<LiveCandleChart> candleChart);

    void enableIndicatorsOnCharts(bool show);
    void onPushStyleVar() override;

private:
    std::shared_ptr<CandleChart> _chart{nullptr};
    std::shared_ptr<LiveCandleChart> _liveChart{nullptr};
};

#endif //BROKERAPP_CHARTVIEW_H
