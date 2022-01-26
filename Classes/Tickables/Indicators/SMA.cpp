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

        insert(value/_averageSize);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }
}

void SMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);

    //get indexes to render #######
    int startIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(), _ticker->getRenderRange().startTime);
    int endIdx = PlotHelper::BinarySearch(_time.data(), 0, _time.size(), _ticker->getRenderRange().endTime);

    if(startIdx == -1)
        startIdx = 0;

    if(endIdx == -1)
        endIdx = getData().size() - 1;

    int size = endIdx - startIdx + 1;

    //#############################

    ImPlot::PlotLine(_plotName.c_str(), &_time[startIdx], &getData()[startIdx], size);
}

void SMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        resetPlot();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::ColorEdit4("Color",{&_color.x});
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

const ImVec4 &SMA::getColor() {
    return _color;
}

SMA::~SMA() {}




