//
// Created by Luiz Veloso on 06/01/22.
//

#include "EMA.h"
#include "../../Tickers/Ticker.h"

EMA::EMA(Ticker *ticker): Indicator(ticker) {
    setPlotName("EMA");
    _uiNodeType = UiNodeType::EMA;
    _nodeType = NodeType::EMA;
}

void EMA::calculate(BarHistory* barHistory)
{
    if(barHistory->size() >= _averageSize)
    {
        double value = 0;

        if (getData().empty()) {
            for(int i = 0; i < _averageSize; i++) {
                value += (*barHistory)(i,BarDataType::CLOSE);
            }
            value /= _averageSize;

        } else {
            double factor = (1.0 * _smothingSize)/(1.0 * (1+_averageSize));
            value = (getData().back() * (1.0 - factor)) + ((*barHistory)(0,BarDataType::CLOSE) * factor); //data[0] é o EMA de ontem (ultimo disponivel).
        }

        insert(value);
        _time.push_back((*barHistory)(0,BarDataType::TIME));
    }
}

void EMA::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    auto renderInfo = getRenderInfo(_ticker);
    ImPlot::PlotLine(_plotName.c_str(), &_time[renderInfo.startIndex], &getData()[renderInfo.startIndex], renderInfo.size);}

void EMA::onPopupRender() {
    if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
        resetPlot();
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

void EMA::resetPlot() {
    Indicator::resetPlot();
    clear();
}

void EMA::setAverageSize(int size) {
    _averageSize = size;
}

int EMA::getAverageSize() const {
    return _averageSize;
}


EMA::~EMA() {

}
