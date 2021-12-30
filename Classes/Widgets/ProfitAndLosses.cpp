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
    if(_strategy->getClosedPositions().empty()) return;

    static float ratios[] = {1};

    bool shouldLinkPlots;
    if(_editor->getContext()->isSimulating())
        shouldLinkPlots = true;
    else
        shouldLinkPlots = true;

    if(!shouldLinkPlots)
        ImPlot::BeginSubplots("##NoLinkSubPlot",1,1,ImVec2(-1,-1),ImPlotSubplotFlags_None,ratios);

    int xFlags;
    int yFlags;
    bool shouldFitRange;
    if(_editor->getContext()->isSimulating()) {
        xFlags = ImPlotAxisFlags_Time | ImPlotAxisFlags_AutoFit;
        yFlags = ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite;
        shouldFitRange = true;
    }
    else{
        xFlags = ImPlotAxisFlags_Time;
        yFlags = ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite;
        shouldFitRange = false;
    }

    if (ImPlot::BeginPlot("##PnL")) {
        ImPlot::SetupAxes(0, 0, xFlags, yFlags);
        ImPlot::SetupAxisLimits(ImAxis_X1, _strategy->time.front(), _strategy->time.back());
        ImPlot::SetupAxisLimits(ImAxis_Y1, _strategy->drawDownMax, _strategy->profitMax);

        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

        //Fit the data manually with some offset
        if(shouldFitRange) {
            double tenBars = 10 * 60 * _strategy->getTicker()->getSymbol()->getTimeIntervalInMinutes();
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_strategy->time.front() - tenBars,
                                                               _strategy->time.back() + tenBars);
            ImPlot::GetCurrentPlot()->Axes[ImAxis_Y1].SetRange(_strategy->drawDownMax, _strategy->profitMax);
        }


        ImDrawList *drawList = ImPlot::GetPlotDrawList();


        //TODO:: use a baseline value as start from context
        double baseLine = 0;
        double cumulatedProfit = baseLine;
        double lastTime = _strategy->getClosedPositions().front().inTime;

        if(!shouldLinkPlots)
            ImPlot::BeginItem("##PnL");

            for(auto& p : _strategy->getClosedPositions()){
                cumulatedProfit += p.profit;
                auto color = cumulatedProfit >= 0 ? Editor::broker_pnl_profit : Editor::broker_pnl_loss;

                double startX = lastTime;
                double startY = baseLine;

                double endX = p.outTime;
                double endY = cumulatedProfit;

                lastTime = endX;

                ImU32 color32 = ImGui::GetColorU32(color);
                ImVec2 startPos = ImPlot::PlotToPixels(startX, startY);
                ImVec2 endPos = ImPlot::PlotToPixels(endX, endY);

                drawList->AddRectFilled(startPos, endPos, color32);

            }

        if(!shouldLinkPlots)
            ImPlot::EndItem();

        ImPlot::EndPlot();
    }

    if(!shouldLinkPlots)
        ImPlot::EndSubplots();

}

void ProfitAndLosses::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ProfitAndLosses::setStrategyTest(TestStrategy *strategy) {
    _strategy = strategy;
}
