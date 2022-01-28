//
// Created by Luiz Veloso on 27/01/22.
//

#include "MFI.h"
#include <iostream>
#include "../../Tickers/Ticker.h"


MFI::MFI(Ticker *ticker): Indicator(ticker) {
    setPlotName("MFI");
}


void MFI::calculate(BarHistory* barHistory)
{
    double lastTypicalPrice = calculateTypicalPrice((*barHistory)(0,BarDataType::LOW),
                                                (*barHistory)(0,BarDataType::HIGH),
                                                (*barHistory)(0,BarDataType::CLOSE));

    if(_typicalPrice.size() == 0) {
        _typicalPrice.push(lastTypicalPrice);
        return;
    }

    if (lastTypicalPrice >= _typicalPrice(0)) {
        _negativeMoneyFlow.push(0);
        _positiveMoneyFlow.push(0,BarDataType::VOLUME);
    } else {
        _negativeMoneyFlow.push(BarDataType::VOLUME);
        _positiveMoneyFlow.push(0);
    };
    _typicalPrice.push(lastTypicalPrice);

    if (_typicalPrice.size() >= _averageSize) {
        double totalPositive = 0, totalNegative = 0;
        for(int i = 0 ; i < _averageSize; i++) {
            totalPositive += _positiveMoneyFlow(i);
            totalNegative += _negativeMoneyFlow(i);
        }

        double ratio = totalPositive/totalNegative;
        double mfi = 100 - (100/(1+ratio));

        push(mfi);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }

}

double MFI::calculateTypicalPrice(double low, double high, double close) {
    return (low + high + close) / 3;
}

void MFI::onRender() {

    auto renderInfo = getRenderInfo(_ticker);
    ImPlot::SetNextLineStyle(_colorTop, _lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &getData()[renderInfo.startIndex], renderInfo.size);

}

void MFI::onPopupRender() {
    if(ImGui::SliderFloat("Upper Band", &_upperBand, 0.01, 1)){
        reset();
        onLoad(_ticker->getBarHistory());
    }

    if(ImGui::SliderFloat("Upper Band", &_lowerBand, 0.01, 1)){
        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();
//    if(ImGui::SliderFloat("Center Threshold", &_lowerBand, 0.01, 1)){
//        _upperBand = 1 - _lowerBand;
//
//        reset();
//        onLoad(_ticker->getBarHistory());
//    }
//    ImGui::Separator();

    ImGui::ColorEdit4("ColorTop",{&_colorTop.x});
    ImGui::ColorEdit4("ColorBottom",{&_colorBottom.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void MFI::reset() {
    Indicator::reset();
    clear();
}

const ImVec4 &MFI::getColor() {
    return _colorBottom;
}

MFI::~MFI() {

}