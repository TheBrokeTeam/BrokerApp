//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Chart.h"
#include "../Editor.h"

Chart::Chart(Editor *editor) : Widget(editor) {
    _title                  = "Chart";
    _is_window              = true;
}

void Chart::updateVisible(float dt) {

    ImGui::TextColored(Editor::broker_white,"Chart");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_clear);

    //adding the close button
    auto info = _editor->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        _editor->showCharts(false);
    }

    ImGui::Separator();

    if(_chart != nullptr)
        _chart->updateVisible(dt);
//    for(auto c : _charts)
//        c->updateVisible(dt);

//    if (ImGui::BeginTabBar("Symbols")) {
//        for(auto c : _charts)
//            c->updateVisible(dt);
//        ImGui::EndTabBar();
//    }
}

void Chart::addChart(std::shared_ptr<CandleChart> candleChart){
    _chart.reset();
    _chart = std::move(candleChart);
}

void Chart::enableIndicatorsOnCharts(bool show) {
    if(_chart != nullptr)
        _chart->showIndicators(show);
}


void Chart::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
