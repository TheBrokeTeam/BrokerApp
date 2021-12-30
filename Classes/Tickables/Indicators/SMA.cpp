//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "SMA.h"
#include <implot.h>
#include <implot_internal.h>

SMA::SMA(Ticker *ticker): Indicator(ticker) {
    setName("SMA");
}

void SMA::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += (*barHistory)[i].close;

        _data.push_back(value/_averageSize);
        _time.push_back((*barHistory)[0].time);
    }
}

void SMA::render() {
    Indicator::render();

    // custom legend context menu
    if (ImPlot::BeginLegendPopup(_name.c_str())) {
        ImGui::Separator();
        if(ImGui::SliderInt("Average size", &_averageSize, 1, 200)){
            reset();
            onLoad(_ticker->getBarHistory());
        }
        ImGui::ColorEdit4("Color",{&_color.x});
        ImGui::Separator();
        ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
        ImPlot::EndLegendPopup();
    }
}

SMA::~SMA() {}

void SMA::setAverageSize(int size) {
    _averageSize = size;
}


