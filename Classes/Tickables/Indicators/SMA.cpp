//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "SMA.h"
#include "../../Tickers/Ticker.h"
#include "../../Helpers/PlotHelper.h"


SMA::SMA(Ticker *ticker): Indicator(ticker) {
    setPlotName("SMA");
}

void SMA::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += (*barHistory)(i,BarDataType::CLOSE);

        push(value / _averageSize);
        _time.push_back((*barHistory)(0,BarDataType::TIME_S));
    }
}

void SMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_ticker);
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &getData()[renderInfo.startIndex], renderInfo.size);
}

void SMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        resetPlot();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::ColorEdit4("Color",&_color.x);
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void SMA::resetPlot() {
    Indicator::resetPlot();
    clear();
}

void SMA::setAverageSize(int size) {
    _averageSize = size;
}

int SMA::getAverageSize() const {
    return _averageSize;
}


SMA::~SMA() {}




