//
// Created by Luiz Veloso on 11/01/22.
//

#include "TRIX.h"
#include <iostream>



TRIX::TRIX(Ticker *ticker): Indicator(ticker) {
    setPlotName("TRIX");
}

double TRIX::calculateEMA(std::vector<double> sequence, int averageSize) {

    if(sequence.size() >= averageSize)
    {
        double value = 0;

        if (sequence.empty()) {
            for(int i = 0; i < averageSize; i++) {
                value += sequence[i];
            }
            value /= averageSize;

        } else {
            double factor = (2.0)/(1.0 * (1+averageSize));
            value = (sequence[1] * (1 - factor)) + (sequence[0] * factor);
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
            e1 = calculateEMA(priceSequence, _averageSize);
            EMA1.insert(EMA1.begin(), e1);
        }

        if (EMA1.size() >= _averageSize) {
            e2 = calculateEMA(EMA1, _averageSize);
            EMA2.insert(EMA2.begin(), e2);
        }

        if (EMA2.size() >= _averageSize) {
            e3 = calculateEMA(EMA2, _averageSize);
            EMA3.insert(EMA3.begin(), e3);
        }

    }

    if (EMA3.size() >= 2) {
        double trix = (EMA3[0] - EMA3[1])/EMA3[1];
        _data.push_back(trix);
        _time.push_back((*barHistory)[0].time);
    }

}

void TRIX::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
//    for (double i: _data)
//            std::cout << i << ' ';
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



TRIX::~TRIX() {

}
