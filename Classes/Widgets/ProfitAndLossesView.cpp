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

    int xFlags = 0;
    int yFlags = 0;

    xFlags = ImPlotAxisFlags_Time;
    xFlags |= ImPlotAxisFlags_AutoFit;


    yFlags = ImPlotAxisFlags_AutoFit;
    yFlags |= ImPlotAxisFlags_RangeFit;
    yFlags |= ImPlotAxisFlags_Opposite;

    static float ratios[] = {1};
    if(ImPlot::BeginSubplots("##NoLinkSubPlot",1,1,ImVec2(-1,-1),ImPlotSubplotFlags_None, ratios)) {
        if (ImPlot::BeginPlot("##PnL", ImVec2(-1, 0), ImPlotFlags_None)) {
            ImPlot::SetupAxes(0, 0, xFlags, yFlags);
            ImPlot::SetupAxisLimits(ImAxis_X1, _plotTime.front(), _plotTime.back());
            ImPlot::SetupAxisLimits(ImAxis_Y1, _strategy.lock()->drawDownMax, _strategy.lock()->profitMax);

            ImPlot::SetupAxisFormat(ImAxis_Y1, "$%.2f");


//        double tenBars = 10 * 60 * _strategy.lock()->getTicker()->getSymbol()->getTimeIntervalInMinutes();
//        ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].SetRange(_strategy.lock()->getTime().front() - tenBars,
//                                                           _strategy.lock()->getTime().back() + tenBars);
//        ImPlot::GetCurrentPlot()->Axes[ImAxis_Y1].SetRange(_strategy.lock()->drawDownMax*1.2, _strategy.lock()->profitMax*1.2);

            int startIndex = _plotTime.size() > _maxPositionsToRender ? _plotTime.size() - _maxPositionsToRender : 0;
            int size = _plotTime.size() > _maxPositionsToRender ? _maxPositionsToRender : _plotTime.size();

            //now plot the data
            ImPlot::SetNextLineStyle(Editor::broker_pnl_profit, 2.0);
            ImPlot::PlotLine("##profitline", &_plotTime[startIndex], &_plotProfit[startIndex], size);
            ImPlot::SetNextFillStyle(Editor::broker_pnl_profit, 0.35);
            ImPlot::PlotShaded("profit", &_plotTime[startIndex], &_plotProfit[startIndex], size, _baseLine);
            ImPlot::SetNextLineStyle(Editor::broker_pnl_loss, 2.0);
            ImPlot::PlotLine("##profitline", &_plotTime[startIndex], &_plotLosses[startIndex], size);
            ImPlot::SetNextFillStyle(Editor::broker_pnl_loss, 0.35);
            ImPlot::PlotShaded("losses", &_plotTime[startIndex], &_plotLosses[startIndex], size, _baseLine);


        //plot render range over plot
        auto drawList = ImPlot::GetPlotDrawList();
        auto colorSquare = ImGui::GetColorU32(ImVec4(Editor::broker_yellow_active.x,Editor::broker_yellow_active.y,Editor::broker_yellow_active.z,0.2f));
        ImVec2 minPoint = ImPlot::PlotToPixels(getContext()->getRenderRange().startTime,_strategy.lock()->drawDownMax*1.2);
        ImVec2 maxPoint = ImPlot::PlotToPixels(getContext()->getRenderRange().endTime,_strategy.lock()->profitMax*1.2);
        drawList->AddRectFilled(minPoint,maxPoint,colorSquare);

            ImPlot::EndPlot();
        }
        ImPlot::EndSubplots();
    }
}

void ProfitAndLossesView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void ProfitAndLossesView::setStrategyTest(std::weak_ptr<Strategy> strategy) {
    _strategy = strategy;
}

void ProfitAndLossesView::onClosePosition(const Strategy::Position &p) {


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

    _closedPositions.push_back(p);

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
