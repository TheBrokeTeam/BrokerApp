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
    clear();
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

        if(!shouldLinkPlots)
            ImPlot::BeginItem("##PnL");

        //now plot the data
        ImPlot::SetNextLineStyle(Editor::broker_pnl_profit,2.0);
        ImPlot::PlotLine("##profitline", _plotTime.data(), _plotProfit.data(), _plotTime.size());
        ImPlot::SetNextFillStyle(Editor::broker_pnl_profit, 0.35);
        ImPlot::PlotShaded("profit", _plotTime.data(), _plotProfit.data(), _plotTime.size(), _baseLine);
        ImPlot::SetNextLineStyle(Editor::broker_pnl_loss,2.0);
        ImPlot::PlotLine("##profitline", _plotTime.data(), _plotLosses.data(), _plotTime.size());
        ImPlot::SetNextFillStyle(Editor::broker_pnl_loss,0.35);
        ImPlot::PlotShaded("losses", _plotTime.data(), _plotLosses.data(), _plotTime.size(), _baseLine);


        //plot ticker range over plot
        auto drawList = ImPlot::GetPlotDrawList();
        auto colorSquare = ImGui::GetColorU32(ImVec4(Editor::broker_yellow_active.x,Editor::broker_yellow_active.y,Editor::broker_yellow_active.z,0.2f));
        ImVec2 minPoint = ImPlot::PlotToPixels(getContext()->getRenderRange().startTime,_strategy.lock()->drawDownMax*1.2);
        ImVec2 maxPoint = ImPlot::PlotToPixels(getContext()->getRenderRange().endTime,_strategy.lock()->profitMax*1.2);
        drawList->AddRectFilled(minPoint,maxPoint,colorSquare);

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

void ProfitAndLossesView::onClosePosition(const Strategy::Position &p) {
    _closedPositions.push_back(p);

    //TODO:: use a baseline value as start from context

    bool isInProfit = _cumulatedProfit >= _baseLine;

    //added info about not trading time
    if(_closedPositions.size() > 0){
        _plotTime.push_back(_lastTime);
        _plotTime.push_back(p.inTime);
        if(isInProfit){
            _plotProfit.push_back(_cumulatedProfit);
            _plotProfit.push_back(_cumulatedProfit);
            _plotLosses.push_back(_baseLine);
            _plotLosses.push_back(_baseLine);
        }
        else{
            _plotProfit.push_back(_baseLine);
            _plotProfit.push_back(_baseLine);
            _plotLosses.push_back(_cumulatedProfit);
            _plotLosses.push_back(_cumulatedProfit);
        }
    }

    double startX = p.inTime;
    double startY = _cumulatedProfit;

    _cumulatedProfit += p.profit;

    double endX = p.outTime;
    double endY = _cumulatedProfit ;

    _lastTime = endX;

    isInProfit = _cumulatedProfit >= _baseLine;

    //cross the baseline profit to down or up
    if( (startY >= _baseLine && endY < _baseLine ) ||
        startY < _baseLine && endY >= _baseLine) {

        double deltaY = endY - startY;
        double deltaX = endX - startX;

        //find the X intersection with the baseline
        double m = deltaY/deltaX;
        double n = startY - m*startX;

        double intersectionX = (_baseLine - n)/m;
        double intersectionY = _baseLine;

        _plotTime.push_back(startX);
        _plotTime.push_back(intersectionX);
        _plotTime.push_back(intersectionX);
        _plotTime.push_back(endX);

        //cross up
        if(isInProfit){
            _plotProfit.push_back(_baseLine);
            _plotProfit.push_back(_baseLine);
            _plotProfit.push_back(intersectionY);
            _plotProfit.push_back(endY);

            _plotLosses.push_back(startY);
            _plotLosses.push_back(intersectionY);
            _plotLosses.push_back(_baseLine);
            _plotLosses.push_back(_baseLine);

        }//corss down
        else{
            _plotProfit.push_back(startY);
            _plotProfit.push_back(intersectionY);
            _plotProfit.push_back(_baseLine);
            _plotProfit.push_back(_baseLine);

            _plotLosses.push_back(_baseLine);
            _plotLosses.push_back(_baseLine);
            _plotLosses.push_back(intersectionY);
            _plotLosses.push_back(endY);
        }
    }
        //not cross the baseline
    else{

        _plotTime.push_back(startX);
        _plotTime.push_back(endX);

        if(isInProfit){
            _plotProfit.push_back(startY);
            _plotProfit.push_back(endY);

            _plotLosses.push_back(_baseLine);
            _plotLosses.push_back(_baseLine);
        }
        else{
            _plotProfit.push_back(_baseLine);
            _plotProfit.push_back(_baseLine);

            _plotLosses.push_back(startY);
            _plotLosses.push_back(endY);
        }
    }
}

void ProfitAndLossesView::clear() {
    _closedPositions.clear();
    _plotTime.clear();
    _plotProfit.clear();
    _plotLosses.clear();
    _cumulatedProfit = _baseLine;
}
