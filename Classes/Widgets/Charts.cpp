//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Charts.h"

Charts::Charts(Editor *editor) : Widget(editor) {
    _title                  = "Charts";
    _is_window              = true;
}

void Charts::updateVisible(float dt) {
    ImGui::SetNextItemWidth(400);
    if (ImGui::BeginTabBar("Symbols")) {
        for(auto c : _charts)
            c->updateVisible(dt);
        ImGui::EndTabBar();
    }
}

void Charts::addChart(std::shared_ptr<CandleChart> candleChart){
    _charts.push_back(candleChart);
}

void Charts::enableIndicatorsOnCharts(bool show) {
    for(auto c : _charts)
        c->showIndicators(show);
}
