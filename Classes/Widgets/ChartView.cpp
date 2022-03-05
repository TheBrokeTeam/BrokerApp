//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "ChartView.h"
#include "../Editor.h"
#include "BrokerColorsImgui.h"

ChartView::ChartView(Context* context) : Widget(context) {
    _title                  = "Chart";
    _is_window              = true;
}

void ChartView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    if(_chart != nullptr)
        _chart->updateVisible(dt);
}

void ChartView::addChart(std::shared_ptr<CandleChart> candleChart){
    _chart.reset();
    _chart = std::move(candleChart);
}

void ChartView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg, BrokerColorsImgui::broker_dark_grey);
}
