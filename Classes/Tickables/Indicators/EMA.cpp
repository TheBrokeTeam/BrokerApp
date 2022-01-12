//
// Created by Luiz Veloso on 06/01/22.
//

#include "EMA.h"

EMA::EMA(Ticker *ticker): Indicator(ticker) {
    setPlotName("EMA");
}

void EMA::calculate(BarHistory* barHistory)
{
    if(barHistory->size() >= _averageSize)
    {
        double value = 0;

        if (_data.empty()) {
            for(int i = 0; i < _averageSize; i++) {
                value += (*barHistory)[i].close;
            }
            value /= _averageSize;

        } else {
            double factor = (1.0 * _smothingSize)/(1.0 * (1+_averageSize));
            value = (_data[0] * (1 - factor)) + ((*barHistory)[0].close * factor); //data[0] é o EMA de ontem (ultimo disponivel).
        }

        _data.push_back(value);
        _time.push_back((*barHistory)[0].time);
    }
}

void EMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void EMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();

//    if(ImGui::SliderInt("Smothing size", &_smothingSize, 1, 2)){
//        reset();
//        onLoad(_ticker->getBarHistory());
//    }

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void EMA::reset() {
    Indicator::reset();
    _data.clear();
}

void EMA::setAverageSize(int size) {
    _averageSize = size;
}

int EMA::getAverageSize() const {
    return _averageSize;
}

void EMA::setSmothingSize(int size) {
    _smothingSize = size;
}

int EMA::getSmothingSize() const {
    return _smothingSize;
}


EMA::~EMA() {

}
