//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "SMA.h"

SMA::SMA(Ticker *ticker): Indicator(ticker) {
    setName("SMA");
}

void SMA::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += (*barHistory)[i].close;

        _data.push_back(value/_averageSize);
        _time.push_back((*barHistory)[0].time);
    }
}

void SMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void SMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void SMA::reset() {
    Indicator::reset();
    _data.clear();
}

void SMA::setAverageSize(int size) {
    _averageSize = size;
}

int SMA::getAverageSize() const {
    return _averageSize;
}




