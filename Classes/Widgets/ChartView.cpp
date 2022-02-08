//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "ChartView.h"
#include "../Editor.h"

ChartView::ChartView(Context* context) : Widget(context) {
    _title                  = "Chart";
    _is_window              = true;
}

void ChartView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    if(_chart != nullptr)
        _chart->updateVisible(dt);

    if(_liveChart != nullptr)
        _liveChart->updateVisible(dt);
}

void ChartView::addChart(std::shared_ptr<CandleChart> candleChart){
    _chart.reset();
    _chart = std::move(candleChart);
}

void ChartView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ChartView::addLiveChart(std::shared_ptr<LiveCandleChart> candleChart) {
    _liveChart.reset();
    _liveChart = std::move(candleChart);
}
