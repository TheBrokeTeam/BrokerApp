//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#include "ProfitAndLossesView.h"
#include "../Editor.h"
#include <implot.h>
#include <implot_internal.h>


ProfitAndLossesView::ProfitAndLossesView(Context* context, Strategy* strategy) : Widget(context) {
    _title                  = "Profit & Losses";
    _is_window              = true;
    _strategy = strategy;
}

void ProfitAndLossesView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //now draw the pnl chart
    if(_strategy == nullptr) return;
    if(_strategy->getClosedPositions().empty()) return;

    static float ratios[] = {1};

    bool shouldLinkPlots;
    if(getContext()->isSimulating())
        shouldLinkPlots = false;
    else
        shouldLinkPlots = false;

    if(!shouldLinkPlots)
        ImPlot::BeginSubplots("##NoLinkSubPlot",1,1,ImVec2(-1,-1),ImPlotSubplotFlags_None,ratios);

    int xFlags;
    int yFlags;
    bool shouldFitRange;
    if(getContext()->isSimulating()) {
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

//        const double candleWidthOffset = (_strategy->getTicker()->getSymbol()->getTimeIntervalInMinutes() * 60)/2.0;

        for(auto& p : _strategy->getClosedPositions()){
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

            auto colorLine = cumulatedProfit >= 0 ? Editor::broker_pnl_profit_line : Editor::broker_pnl_loss_line;
            ImU32 colorLine32 = ImGui::GetColorU32(colorLine);

            ImVec2 lineLeft = ImPlot::PlotToPixels(startX, endY);
            ImVec2 lineRight = ImPlot::PlotToPixels(endX, endY);
            drawList->AddLine(lineLeft, lineRight, colorLine32, 2.0f);

            cumulatedProfit += p.profit;

        }

        if(!shouldLinkPlots)
            ImPlot::EndItem();

        ImPlot::EndPlot();
    }

    if(!shouldLinkPlots)
        ImPlot::EndSubplots();

}

void ProfitAndLossesView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ProfitAndLossesView::setStrategyTest(IndicatorFromChartExample *strategy) {
    _strategy = strategy;
}
