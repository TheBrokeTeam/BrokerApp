//
// Created by Luiz Veloso on 27/01/22.
//

#include "MFI.h"
#include <iostream>
#include "../../Tickers/Ticker.h"
#include "../../Contexts/Context.h"


MFI::MFI(Ticker *ticker): Indicator(ticker) {
    setPlotName("MFI");
    setIsSubplot(true);
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
        _negativeMoneyFlow.push(0.0);
        _positiveMoneyFlow.push(lastTypicalPrice * (*barHistory)(0,BarDataType::VOLUME));
    } else {
        _negativeMoneyFlow.push(lastTypicalPrice * (*barHistory)(0,BarDataType::VOLUME));
        _positiveMoneyFlow.push(0);
    };
    _typicalPrice.push(lastTypicalPrice);

    if (_positiveMoneyFlow.size() >= _averageSize) {
        double totalPositive = 0, totalNegative = 0;
        for(int i = 0 ; i < _averageSize; i++) {
            totalPositive += _positiveMoneyFlow(i);
            totalNegative += _negativeMoneyFlow(i);
        }

        double ratio = totalPositive/totalNegative;
        double mfi = 100.0 - (100.0/(1+ratio));

        push(mfi);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }

}

double MFI::calculateTypicalPrice(double low, double high, double close) {
    return (low + high + close) / 3;
}

void MFI::onSetupPlot() {
    int xFlags = ImPlotAxisFlags_Time;
    xFlags |= ImPlotAxisFlags_NoTickLabels;

    ImPlot::SetupAxes(nullptr, nullptr, xFlags ,ImPlotAxisFlags_LockMax|ImPlotAxisFlags_LockMin|ImPlotAxisFlags_Opposite);

    ImPlot::GetCurrentPlot()->Axes[ImAxis_X1].zoomOutMax = getContext()->getZoomOutMax();

    ImPlot::SetupAxisLimits(ImAxis_Y1, 0,100.0);

    ImPlot::SetupAxisLimits(ImAxis_X1, getContext()->getRenderRange().startTime,getContext()->getRenderRange().endTime);
    ImPlot::SetupAxisFormat(ImAxis_Y1, "%.0f");
}

void MFI::onRender() {


    ImPlot::SetNextLineStyle(_color, _lineWidth);
    auto renderInfo = getRenderInfo(_ticker);
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &getData()[renderInfo.startIndex], renderInfo.size);

    std::ostringstream strs;
    strs << std::fixed << std::setprecision(1)  << _upperBand;
    std::string upperStr = strs.str();

    std::ostringstream strs2;
    strs2 << std::fixed << std::setprecision(1)  << _centerBand;
    std::string centerStr = strs2.str();

    std::ostringstream strs3;
    strs3 << std::fixed << std::setprecision(1)  << _lowerBand;
    std::string lowerStr = strs3.str();


    if (_doubleBands) {
        ImPlot::SetNextLineStyle(_colorTop, 1.5);
        double upperBand[] = {_upperBand};
        std::string upperBandLegend = std::string("Upper Band (") + upperStr + std::string(")");
        ImPlot::PlotHLines(upperBandLegend.c_str(), upperBand, 1);

        ImPlot::SetNextLineStyle(_colorBottom, 1.5);
        double lowerBand[] = {_lowerBand};
        std::string lowerBandLegend = std::string("Lower Band (") + lowerStr + std::string(")");
        ImPlot::PlotHLines(lowerBandLegend.c_str(), lowerBand, 1);
    } else {
        ImPlot::SetNextLineStyle(_colorCenter, 1.5);
        double centerBand[] = {_centerBand};
        std::string centerBandLegend = std::string("Threshold (") + centerStr + std::string(")");
        ImPlot::PlotHLines(centerBandLegend.c_str(), centerBand, 1);
    }
}

void MFI::onPopupRender() {

    const char* items[] = {"Threshold", "Bands"};
    static int item_current = _doubleBands ? 1 : 0;
    if (ImGui::Combo("Type", &item_current, items, IM_ARRAYSIZE(items))) {
        _doubleBands = static_cast<bool>(item_current);
    }

    if (_doubleBands) {
        if (ImGui::SliderFloat("Upper Band", &_upperBand, _lowerBand, 99, "%.1f", ImGuiSliderFlags_ClampOnInput)) {}
        ImGui::ColorEdit4("Upper Color",&_colorTop.x);
//
//
        if(ImGui::SliderFloat("Lower Band", &_lowerBand, 1.0, _upperBand, "%.1f", ImGuiSliderFlags_ClampOnInput)) {}
        ImGui::ColorEdit4("Lower Color",&_colorBottom.x);
    } else {
        if(ImGui::SliderFloat("Threshold", &_centerBand, 1.0, 99, "%.1f", ImGuiSliderFlags_ClampOnInput)) {}
        ImGui::ColorEdit4("Threshold Color",&_colorCenter.x);
    }
    ImGui::Separator();

    ImGui::ColorEdit4("Color",&_color.x);
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5, "%.1f", ImGuiSliderFlags_ClampOnInput);
}

void MFI::reset() {
    Indicator::reset();
    clear();
}


const ImVec4 &MFI::getColor() {
    return _color;
}

MFI::~MFI() {

}