//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#include "Charts.h"
#include "../Editor.h"

Charts::Charts(Editor *editor) : Widget(editor), Contextualizable(editor->getContext()) {
    _title                  = "Charts";
    _is_window              = true;
}

void Charts::updateVisible(float dt) {

    ImGui::TextColored(Editor::broker_white,"Charts");
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

    for(auto c : _charts)
        c->updateVisible(dt);

//    if (ImGui::BeginTabBar("Symbols")) {
//        for(auto c : _charts)
//            c->updateVisible(dt);
//        ImGui::EndTabBar();
//    }
}

void Charts::addChart(std::shared_ptr<CandleChart> candleChart){
    _charts.push_back(candleChart);
}

void Charts::enableIndicatorsOnCharts(bool show) {
    for(auto c : _charts)
        c->showIndicators(show);
}


void Charts::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
