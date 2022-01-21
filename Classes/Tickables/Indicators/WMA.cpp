//
// Created by Luiz Veloso on 11/01/22.
//

#include "WMA.h"
#include "../../Tickers/Ticker.h"


WMA::WMA(Ticker *ticker): Indicator(ticker) {
    setPlotName("WMA");
}

int WMA::sumNfirst(int number) {
    return int((float(1+number)/2.0) * number);
}

void WMA::calculate(BarHistory* barHistory)
{
    if(barHistory->size() >= _averageSize)
    {
        double value = 0;

        for(int i = 0; i < _averageSize; i++) {
            value += (*barHistory)[i].close * double(_averageSize - i);
        }
        value /= sumNfirst(_averageSize);

        _data.push_back(value);
        _time.push_back((*barHistory)[0].time);
    }
}

void WMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void WMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void WMA::reset() {
    Indicator::reset();
    _data.clear();
}

const ImVec4 &WMA::getColor() {
    return _color;
}

WMA::~WMA() {

}