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

    static float ratios[] = {1};
    if(ImPlot::BeginSubplots("##NoLinkSubPlot",1,1,ImVec2(-1,-1),ImPlotSubplotFlags_None,ratios))
    {
        if (ImPlot::BeginPlot("##PnL")) {
            ImPlot::SetupAxes(0, 0, ImPlotAxisFlags_Time,
                              ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite);
            ImPlot::SetupAxisLimits(ImAxis_X1, _strategy->time.front(), _strategy->time.back());
            ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

            //Fit the data manually with some offset
            double tenBars = 10*60*_strategy->getTicker()->getSymbol()->getTimeIntervalInMinutes();
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_strategy->time.front() - tenBars,_strategy->time.back() + tenBars);

            if (ImPlot::BeginItem("##PnL")) {

                ImPlot::SetNextFillStyle(Editor::broker_pnl_profit);
                ImPlot::PlotShaded("##pnl_fill", _strategy->time.data(), _strategy->profitHistory.data(), _strategy->time.size(), 0.0f);

                ImPlot::SetNextFillStyle(Editor::broker_pnl_loss);
                ImPlot::PlotShaded("##pnl_fill", _strategy->time.data(), _strategy->lossesHistory.data(), _strategy->time.size(), 0.0f);

                ImPlot::EndItem();
            }
            ImPlot::EndPlot();
        }
        ImPlot::EndSubplots();
    }

}

void ProfitAndLosses::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ProfitAndLosses::setStrategyTest(TestStrategy *strategy) {
    _strategy = strategy;
}
