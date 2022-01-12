//
// Created by Luiz Veloso on 11/01/22.
//

#include "TRIX.h"



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
            value = (sequence.back() * (1 - factor)) + (sequence[0] * factor);
        }
        sequence.push_back(value);
        return value;
    }
}

void TRIX::calculate(BarHistory* barHistory)
{
    if(barHistory->size() != 0) {
       priceSequence.push_back((*barHistory)[0].close);
       EMA1.push_back(calculateEMA(priceSequence, _averageSize));
       EMA2.push_back(calculateEMA(EMA1, _averageSize));
       EMA3.push_back(calculateEMA(EMA2, _averageSize));
    }


//    if(barHistory->size() >= _averageSize * 2) {
//        //calcula EM2
//    }
//
//    if(barHistory->size() >= _averageSize * 3) {
//        //calcula EM3
//    }
//
//    if(barHistory->size() >= (_averageSize * 3 + 2)) {
//        //calcula TRIX
//    }


//
//        std::tuple<std::vector<double>, std::vector<double>> EMA;
//        EMA = calculateEMA(barHistory);
//        EMA = calculateEMA(EMA)
    if (EMA3.size() >= 2) {
        _data.push_back((EMA3[0] - EMA3[1])/EMA3[1]);
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



TRIX::~TRIX() {

}
