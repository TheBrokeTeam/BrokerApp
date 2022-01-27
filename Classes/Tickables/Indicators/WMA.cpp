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
            value += (*barHistory)(i,BarDataType::CLOSE) * double(_averageSize - i);
        }
        value /= sumNfirst(_averageSize);

        insert(value);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }
}

void WMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_ticker);
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &getData()[renderInfo.startIndex], renderInfo.size);
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
    clear();
}

const ImVec4 &WMA::getColor() {
    return _color;
}

WMA::~WMA() {}