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

    if (lastTypicalPrice >= _typicalPrice[0]) {
        _negativeMoneyFlow.insert(_negativeMoneyFlow.begin(), 0);
        _positiveMoneyFlow.insert(_positiveMoneyFlow.begin(), lastTypicalPrice * (*barHistory)(0,BarDataType::VOLUME));
    } else {
        _negativeMoneyFlow.insert(_negativeMoneyFlow.begin(), lastTypicalPrice * (*barHistory)(0,BarDataType::VOLUME));
        _positiveMoneyFlow.insert(_positiveMoneyFlow.begin(), 0);
    };
    _typicalPrice.insert(_typicalPrice.begin(), lastTypicalPrice);

    if (_typicalPrice.size() >= _averageSize) {
        double totalPositive = 0, totalNegative = 0;
        for(int i = 0 ; i < _averageSize; i++) {
            totalPositive += _positiveMoneyFlow[i];
            totalNegative += _negativeMoneyFlow[i];
        }

        double ratio = totalPositive/totalNegative;
        double mfi = 100 - (100/(1+ratio));

        // starting period indexes logic
        if (_typicalPrice.size() == _averageSize) {

            if (mfi >= _upperBand) {
                _periodType == 1;
                _startUpperLineIndexes.push_back(0);
            } else if (mfi < _lowerBand) {
                _periodType == -1;
                _startLowerLineIndexes.push_back(0);
            } else {
                _periodType == 0;
                _startCenterLineIndexes.push_back(0);
            }
        }

        //this period type
        int lastPeriodType = 0;

        if (mfi >= _upperBand) {
            lastPeriodType == 1;
        } else if (mfi < _lowerBand) {
            lastPeriodType == -1;
        } else {
            lastPeriodType == 0;
        }

        if (_periodType != lastPeriodType) {
            if (_periodType == 1) {
                _endUpperLineIndexes.push_back(0);
            } else if (_periodType == -1) {
                _endLowerLineIndexes.push_back(0);
            } else {
                _endCenterLineIndexes.push_back(0);
            }

            if (lastPeriodType == 1) {
                _startUpperLineIndexes.push_back(0);
            } else if (lastPeriodType == -1) {
                _startLowerLineIndexes.push_back(0);
            } else {
                _startCenterLineIndexes.push_back(0);
            }
        }

        insert(mfi);
        _time.push_back((*barHistory)(0,BarDataType::TIME));

    }


}

double MFI::calculateTypicalPrice(double low, double high, double close) {
    return (low + high + close) / 3;
}

void MFI::onRender() {

    auto renderInfo = getRenderInfo(_ticker);

    
    for(int i = 0 ; i < _startUpperLineIndexes.size(); i+= 2) {
        ImPlot::SetNextLineStyle(_colorTop, _lineWidth);
        int startIdx, endIdx;

        if(_lineIndexes[i] < renderInfo.startIndex)
            startIdx = renderInfo.startIndex;
        else
            startIdx =_lineIndexes[i] ;

        if(_lineIndexes[i+1] > renderInfo.startIndex + renderInfo.size)
            endIdx = renderInfo.startIndex + renderInfo.size;
        else
            endIdx =_lineIndexes[i+1] ;

        ImPlot::PlotLine(_plotName.c_str(), &_time[startIdx], &getData()[startIdx], endIdx - startIdx + 1);
    }
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
    if(ImGui::SliderFloat("Center Threshold", &_lowerBand, 0.01, 1)){
        _upperBand = 1 - _lowerBand;

        reset();
        onLoad(_ticker->getBarHistory());
    }
    ImGui::Separator();

    ImGui::ColorEdit4("ColorTop",{&_colorTop.x});
    ImGui::ColorEdit4("ColorBottom",{&_colorBottom.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void MFI::reset() {
    Indicator::reset();
    clear();
    //reset time on parent class Plot Item
    resetPlot();
}

const ImVec4 &MFI::getColor() {
    return _colorBottom;
}

MFI::~MFI() {

}