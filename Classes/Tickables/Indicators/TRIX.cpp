//
// Created by Luiz Veloso on 11/01/22.
//

#include "TRIX.h"



TRIX::TRIX(Ticker *ticker): Indicator(ticker) {
    setPlotName("TRIX");
}

std::tuple<std::vector<double>, std::vector<double>> TRIX::calculateEMA(BarHistory* barHistory) {

    if(barHistory->size() >= _averageSize)
    {
        double value = 0;
        std::vector<double> data;
        std::vector<double> time;

        if (data.empty()) {
            for(int i = 0; i < _averageSize; i++) {
                value += (*barHistory)[i].close;
            }
            value /= _averageSize;

        } else {
            double factor = (1.0 * _smothingSize)/(1.0 * (1+_averageSize));
            value = (data.back() * (1 - factor)) + ((*barHistory)[0].close * factor);
        }

        data.push_back(value);
        time.push_back((*barHistory)[0].time);

        return {data, time};
    }
}

void TRIX::calculate(BarHistory* barHistory)
{

    if(barHistory->size() >= _averageSize) {
        //calcula EM1
    }

    if(barHistory->size() >= _averageSize * 2) {
        //calcula EM2
    }

    if(barHistory->size() >= _averageSize * 3) {
        //calcula EM3
    }

    if(barHistory->size() >= (_averageSize * 3 + 2)) {
        //calcula TRIX
    }


    double value = 0;

        std::tuple<std::vector<double>, std::vector<double>> EMA;
        EMA = calculateEMA(barHistory);
        EMA = calculateEMA(EMA)

        _data.push_back(value);
        _time.push_back((*barHistory)[0].time);
    }
}

void TRIX::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void TRIX::onPopupRender() {
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

void TRIX::reset() {
    Indicator::reset();
    _data.clear();
}

void TRIX::setAverageSize(int size) {
    _averageSize = size;
}

int TRIX::getAverageSize() const {
    return _averageSize;
}

void TRIX::setSmothingSize(int size) {
    _smothingSize = size;
}

int TRIX::getSmothingSize() const {
    return _smothingSize;
}


TRIX::~TRIX() {

}
