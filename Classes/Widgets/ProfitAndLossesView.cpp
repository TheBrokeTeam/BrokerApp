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
    if(_closedPositions.empty()) return;

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
    bool shouldFitRange = true;
    if(getContext()->isSimulating()) {
        xFlags = ImPlotAxisFlags_Time | ImPlotAxisFlags_AutoFit;
        yFlags = ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite;
//        shouldFitRange = true;
    }
    else{
        xFlags = ImPlotAxisFlags_Time;
        yFlags = ImPlotAxisFlags_AutoFit | ImPlotAxisFlags_RangeFit | ImPlotAxisFlags_Opposite;
//        shouldFitRange = false;
    }

    if (ImPlot::BeginPlot("##PnL",ImVec2(-1,0),ImPlotFlags_NoInputs)) {
        ImPlot::SetupAxes(0, 0, xFlags, yFlags);
        ImPlot::SetupAxisLimits(ImAxis_X1, _strategy.lock()->getTime().front(), _strategy.lock()->getTime().back());
        ImPlot::SetupAxisLimits(ImAxis_Y1, _strategy.lock()->drawDownMax, _strategy.lock()->profitMax);

        ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");

        //Fit the data manually with some offset
        if(shouldFitRange) {
            double tenBars = 10 * 60 * _strategy.lock()->getTicker()->getSymbol()->getTimeIntervalInMinutes();
            ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_strategy.lock()->getTime().front() - tenBars,
                                                               _strategy.lock()->getTime().back() + tenBars);
            ImPlot::GetCurrentPlot()->Axes[ImAxis_Y1].SetRange(_strategy.lock()->drawDownMax*1.2, _strategy.lock()->profitMax*1.2);
        }


        //TODO:: use a baseline value as start from context
        double baseLine = 0;
        double cumulatedProfit = baseLine;

        double lastTime;
        double lastCumulatedProfit;


        if(!shouldLinkPlots)
            ImPlot::BeginItem("##PnL");

        std::vector<double> plotTime;
        std::vector<double> plotProfit;
        std::vector<double> plotLosses;

        for(int i = 0; i <= _closedPositions.size() - 1; i++)
        {
            auto& p = _closedPositions.at(i);

            bool isInProfit = cumulatedProfit >= baseLine;

            //added info about not trading time
            if(i > 0){
                plotTime.push_back(lastTime);
                plotTime.push_back(p.inTime);
                if(isInProfit){
                    plotProfit.push_back(cumulatedProfit);
                    plotProfit.push_back(cumulatedProfit);
                    plotLosses.push_back(baseLine);
                    plotLosses.push_back(baseLine);
                }
                else{
                    plotProfit.push_back(baseLine);
                    plotProfit.push_back(baseLine);
                    plotLosses.push_back(cumulatedProfit);
                    plotLosses.push_back(cumulatedProfit);
                }
            }

            double startX = p.inTime;
            double startY = cumulatedProfit;

            cumulatedProfit += p.profit;

            double endX = p.outTime;
            double endY = cumulatedProfit ;

            lastTime = endX;

            isInProfit = cumulatedProfit >= baseLine;

            //cross the baseline profit to down or up
            if( (startY >= baseLine && endY < baseLine ) ||
                    startY < baseLine && endY >= baseLine) {

                double deltaY = endY - startY;
                double deltaX = endX - startX;

                //find the X intersection with the baseline
                double m = deltaY/deltaX;
                double n = startY - m*startX;

                double intersectionX = (baseLine - n)/m;
                double intersectionY = baseLine;

                plotTime.push_back(startX);
                plotTime.push_back(intersectionX);
                plotTime.push_back(intersectionX);
                plotTime.push_back(endX);

                //cross up
                if(isInProfit){
                    plotProfit.push_back(baseLine);
                    plotProfit.push_back(baseLine);
                    plotProfit.push_back(intersectionY);
                    plotProfit.push_back(endY);

                    plotLosses.push_back(startY);
                    plotLosses.push_back(intersectionY);
                    plotLosses.push_back(baseLine);
                    plotLosses.push_back(baseLine);

                }//corss down
                else{
                    plotProfit.push_back(startY);
                    plotProfit.push_back(intersectionY);
                    plotProfit.push_back(baseLine);
                    plotProfit.push_back(baseLine);

                    plotLosses.push_back(baseLine);
                    plotLosses.push_back(baseLine);
                    plotLosses.push_back(intersectionY);
                    plotLosses.push_back(endY);
                }
            }
            //not cross the baseline
            else{

                plotTime.push_back(startX);
                plotTime.push_back(endX);

                if(isInProfit){
                    plotProfit.push_back(startY);
                    plotProfit.push_back(endY);

                    plotLosses.push_back(baseLine);
                    plotLosses.push_back(baseLine);
                }
                else{
                    plotProfit.push_back(baseLine);
                    plotProfit.push_back(baseLine);

                    plotLosses.push_back(startY);
                    plotLosses.push_back(endY);
                }
            }
        }

        //now plot the data
        ImPlot::SetNextLineStyle(Editor::broker_pnl_profit,2.0);
        ImPlot::PlotLine("##profitline", plotTime.data(), plotProfit.data(), plotTime.size());
        ImPlot::SetNextFillStyle(Editor::broker_pnl_profit, 0.35);
        ImPlot::PlotShaded("profit",plotTime.data(),plotProfit.data(),plotTime.size(),baseLine);
        ImPlot::SetNextLineStyle(Editor::broker_pnl_loss,2.0);
        ImPlot::PlotLine("##profitline", plotTime.data(), plotLosses.data(), plotTime.size());
        ImPlot::SetNextFillStyle(Editor::broker_pnl_loss,0.35);
        ImPlot::PlotShaded("losses",plotTime.data(),plotLosses.data(),plotTime.size(),baseLine);


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

void ProfitAndLossesView::onClosePosition(const Strategy::Position &pos) {
    _closedPositions.push_back(pos);
}

void ProfitAndLossesView::clear() {
    _closedPositions.clear();
}
