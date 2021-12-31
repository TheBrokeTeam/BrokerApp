//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Chart.h"
#include "../Editor.h"

Chart::Chart(Context* context) : Widget(context) {
    _title                  = "Chart";
    _is_window              = true;
}

void Chart::updateVisible(float dt) {
    Widget::updateVisible(dt);

    if(_chart != nullptr)
        _chart->updateVisible(dt);
}

void Chart::addChart(std::shared_ptr<CandleChart> candleChart){
    _chart.reset();
    _chart = std::move(candleChart);
}

void Chart::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
