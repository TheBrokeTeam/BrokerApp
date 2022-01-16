//
// Created by Arthur Abel Motelevicz on 30/12/21.
//

#include "ProfitAndLossesView.h"
#include "../Editor.h"
#include <implot.h>
#include <implot_internal.h>

ProfitAndLossesView::ProfitAndLossesView(Context* context) : Widget(context) {
    _title                  = "Profit & Losses";
    _is_window              = true;
}

void ProfitAndLossesView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //now draw the pnl chart
    if(!_strategy.lock()) return;
    if(_strategy.lock()->getClosedPositions().empty()) return;

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
        ImPlot::SetupAxisLimits(ImAxis_X1, _strategy.lock()->getTime().front(), _strategy.lock()->getTime().back());
        ImPlot::SetupAxisLimits(ImAxis_Y1, _strategy.lock()->drawDownMax, _strategy.lock()->profitMax);

        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

        //Fit the data manually with some offset
        if(shouldFitRange) {
            double tenBars = 10 * 60 * _strategy.lock()->getTicker()->getSymbol()->getTimeIntervalInMinutes();
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_strategy.lock()->getTime().front() - tenBars,
                                                               _strategy.lock()->getTime().back() + tenBars);
            ImPlot::GetCurrentPlot()->Axes[ImAxis_Y1].SetRange(_strategy.lock()->drawDownMax, _strategy.lock()->profitMax);
        }


        ImDrawList *drawList = ImPlot::GetPlotDrawList();


        //TODO:: use a baseline value as start from context
        double baseLine = 0;
        double cumulatedProfit = baseLine;

        double lastTime;
        double lastCumulatedProfit = _strategy.lock()->getClosedPositions().front().profit;


        if(!shouldLinkPlots)
            ImPlot::BeginItem("##PnL");

//        const double candleWidthOffset = (_strategy.lock()->getTicker()->getSymbol()->getTimeIntervalInMinutes() * 60)/2.0;

//        for(auto& p : _strategy.lock()->getClosedPositions()){
        std::vector<double> plotTime;
        std::vector<double> plotProfit;
        std::vector<double> plotLosses;



        for(int i = 0; i < _strategy.lock()->getClosedPositions().size() - 1; i++)
        {

            auto& p = _strategy.lock()->getClosedPositions().at(i);

            auto color = cumulatedProfit >= 0 ? Editor::broker_pnl_profit : Editor::broker_pnl_loss;

            double startX = p.inTime;
            double startY = cumulatedProfit;

            double endX = p.outTime;
            double endY = cumulatedProfit + p.profit;

            plotTime.push_back(startX);
            plotTime.push_back(endX);
            //cross the baseline profit
            if(cumulatedProfit >= baseLine && endY < baseLine) {
                plotProfit.push_back(cumulatedProfit);\
                plotProfit.push_back(cumulatedProfit);

            }

//            ImU32 color32 = ImGui::GetColorU32(color);
//            ImVec2 startPos = ImPlot::PlotToPixels(startX, startY);
//            ImVec2 endPos = ImPlot::PlotToPixels(endX, endY);
//            ImVec2 basePosRight = ImPlot::PlotToPixels(endX, baseLine);
//            ImVec2 basePosLeft= ImPlot::PlotToPixels(startX, baseLine);
//
//            drawList->AddTriangleFilled(startPos,basePosLeft,basePosRight,color32);
//            drawList->AddTriangleFilled(startPos,endPos,basePosRight,color32);
//
//            auto colorLine = cumulatedProfit >= 0 ? Editor::broker_pnl_profit_line : Editor::broker_pnl_loss_line;
//            ImU32 colorLine32 = ImGui::GetColorU32(colorLine);
//
//            ImVec2 lineLeft = ImPlot::PlotToPixels(startX, startY);
//            ImVec2 lineRight = ImPlot::PlotToPixels(endX, endY);
//            drawList->AddLine(lineLeft, lineRight, colorLine32, 2.0f);
//
//
            if(i > 0){
                plotTime.push_back(lastTime);
                plotTime.push_back(startX);

//                ImVec2 lastEndPos = ImPlot::PlotToPixels(lastTime, lastCumulatedProfit);
//                ImVec2 nextStartPos = ImPlot::PlotToPixels(startX, baseLine);
//                drawList->AddRectFilled(lastEndPos,nextStartPos, color32);
            }

            lastTime = p.outTime;
            cumulatedProfit += p.profit;

            lastCumulatedProfit = cumulatedProfit;

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

void ProfitAndLossesView::setStrategyTest(std::weak_ptr<Strategy> strategy) {
    _strategy = strategy;
}
