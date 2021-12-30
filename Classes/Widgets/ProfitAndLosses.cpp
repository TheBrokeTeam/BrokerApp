//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#include "ProfitAndLosses.h"
#include "../Editor.h"
#include <implot.h>
#include <implot_internal.h>


ProfitAndLosses::ProfitAndLosses(Editor *editor, Strategy* strategy) : Widget(editor) {
    _title                  = "ProfitAndLosses";
    _is_window              = true;
    _strategy = strategy;
}

void ProfitAndLosses::updateVisible(float dt) {

    ImGui::TextColored(Editor::broker_white,"Profit & Losses");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_clear);

    //adding the close button
    auto info = _editor->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);

    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        //TODO:: close this view from editor call
    }

    ImGui::Separator();

    //now draw the pnl chart

    if(_strategy == nullptr) return;
    if(_strategy->time.empty()) return;

    if (ImPlot::BeginPlot("##PnL")) {
        ImPlot::SetupAxes(0, 0, ImPlotAxisFlags_Time | ImPlotAxisFlags_NoTickLabels,
                          ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite);
        ImPlot::SetupAxisLimits(ImAxis_X1, _strategy->time.front(), _strategy->time.back());
        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

        ImDrawList *drawList = ImPlot::GetPlotDrawList();

        if (ImPlot::BeginItem("PnL")) {
            // fit data on screen even when zooming
            if (ImPlot::FitThisFrame()) {
                for (int i = 0; i < _strategy->profitHistory.size(); ++i) {
                    ImPlot::FitPoint(ImPlotPoint(_strategy->time[i], _strategy->profitHistory[i]));
                }
            }


            ImPlot::SetNextLineStyle(_color,2.0f);
            ImPlot::PlotLine("##pnl", _strategy->time.data(), _strategy->profitHistory.data(), _strategy->time.size());

            ImPlot::EndItem();
        }
        ImPlot::EndPlot();
    }
}

void ProfitAndLosses::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ProfitAndLosses::setStrategyTest(TestStrategy *strategy) {
    _strategy = strategy;
}
