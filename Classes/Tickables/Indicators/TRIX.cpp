//
// Created by Luiz Veloso on 11/01/22.
//

#include "TRIX.h"
#include "../../Widgets/IndicatorsView.h"
#include <iostream>
#include "../../Tickers/Ticker.h"


TRIX::TRIX(Ticker *ticker): Indicator(ticker) {
    setPlotName("TRIX");
}

double TRIX::calculateEMA(std::vector<double> origin,std::vector<double> destination, int averageSize) {

    if(origin.size() >= averageSize)
    {
        double value = 0;

        if (destination.empty()) {
            for(int i = 0; i < averageSize; i++) {
                value += origin[i];
            }
            value /= averageSize;

        } else {
            double factor = (2.0)/(1.0 * (1+averageSize));
            value = (destination[0] * (1 - factor)) + (origin[0] * factor); // (lv) destination[0] é equivalente ao valor do periodo anterior da sequencia de destino (que está sendo atualizada agora).
        }
        return value;
    }
}

void TRIX::calculate(BarHistory* barHistory)
{
    if(barHistory->size() != 0) {
        priceSequence.insert(priceSequence.begin(), (*barHistory)[0].close);

        double e1, e2, e3;

        if (priceSequence.size() >= _averageSize) {
            e1 = calculateEMA(priceSequence, EMA1, _averageSize);
            EMA1.insert(EMA1.begin(), e1);
        }

        if (EMA1.size() >= _averageSize) {
            e2 = calculateEMA(EMA1, EMA2, _averageSize);
            EMA2.insert(EMA2.begin(), e2);
        }

        if (EMA2.size() >= _averageSize) {
            e3 = calculateEMA(EMA2, EMA3, _averageSize);
            EMA3.insert(EMA3.begin(), e3);
        }

    }

    if (EMA3.size() >= 2) {
        double trix = (EMA3[0] - EMA3[1])/EMA3[1];
        _data.push_back(trix * 100); // todo: remover * 100. apenas para ajudar no teste até finalizar o TRIXNode.
        _time.push_back((*barHistory)[0].time);
    }

}

void TRIX::onRender() {}

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

void TRIX::render() {

    int xFlags = ImPlotAxisFlags_Time;
    xFlags |= ImPlotAxisFlags_NoTickLabels;

    ImPlot::SetupAxes(nullptr, nullptr, xFlags ,ImPlotAxisFlags_AutoFit|ImPlotAxisFlags_RangeFit|ImPlotAxisFlags_Opposite);

    ImPlot::SetupAxisLimits(ImAxis_X1, _time.front(),_time.back());
    ImPlot::SetupAxisFormat(ImAxis_Y1, "%.2f%%");

    // fit data on screen even when zooming
    if (ImPlot::FitThisFrame()) {
        for (int i = 0; i < _data.size(); ++i) {
            ImPlot::FitPoint(ImPlotPoint(_time[i], _data[i]));
        }
    }

    ImPlot::SetNextLineStyle(_color, _lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());

}

const ImVec4 &TRIX::getColor() {
    return _color;
}


TRIX::~TRIX() {}


