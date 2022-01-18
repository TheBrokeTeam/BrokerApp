//
// Created by Luiz Veloso on 18/01/22.
//

#include "VWAP.h"



VWAP::VWAP(Ticker *ticker): Indicator(ticker) {
    setPlotName("VWAP");
}

void VWAP::calculate(BarHistory* barHistory)
{
    if((*barHistory).getTimeData() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += (*barHistory)[i].close;

        _data.push_back(value/_averageSize);
        _time.push_back((*barHistory)[0].time);
    }
}

void VWAP::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void VWAP::onPopupRender() {

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void VWAP::reset() {
    Indicator::reset();
    _data.clear();
}

void VWAP::setupNewDay() {
    _accTypicalPriceWeighted = 0;
    _accVolume = 0;
}

const ImVec4 &VWAP::getColor() {
    return _color;
}

VWAP::~VWAP() {

}




