//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "SMA.h"
#include <implot.h>
#include <implot_internal.h>

SMA::SMA(Ticker *ticker): Indicator(ticker) {
    setName("MA");
}

void SMA::calculate()
{
    if(_barHistory->size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += barHist[i].close;

        _data.push_back(value/_averageSize);
        _time.push_back(barHist[0].time);
    }
}


SMA::~SMA() {}

void SMA::onLoad(BarHistory *barHistory) {
    Indicator::onLoad(barHistory);

    auto& data = _barHistory->getData();

    if(data.size() >= _averageSize){
        for(int idx = _averageSize; idx < data.size(); idx++) {
            double value = 0;
            for (int i = 0; i < _averageSize; i++)
                value += data[idx - i].close;

            _data.push_back(value / _averageSize);
            _time.push_back(data[idx].time);
        }
    }
}

void SMA::render() {
    Indicator::render();

    // custom legend context menu
    if (ImPlot::BeginLegendPopup(_name.c_str())) {
        ImGui::Separator();
        if(ImGui::SliderInt("Average size", &_averageSize, 0, 200)){
            reset();
            onLoad(_barHistory);
        }
        ImGui::ColorEdit4("Color",{&_color.x});
        ImGui::Separator();
        ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
        ImPlot::EndLegendPopup();
    }

}

