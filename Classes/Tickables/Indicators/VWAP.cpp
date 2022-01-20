//
// Created by Luiz Veloso on 18/01/22.
//

#include "VWAP.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;


VWAP::VWAP(Ticker *ticker): Indicator(ticker) {
    setPlotName("VWAP");
}

void VWAP::calculate(BarHistory* barHistory)
{
    if (isNewPeriod((*barHistory).getTimeData().front(), Day)) {
        setupNewPeriod();
    }
    
    double lastVolume = (*barHistory).getVolumeData().front();
    BarData lastData = (*barHistory).getData().front();
    double typicalPrice = calculateTypicalPrice(lastData.low, lastData.high, lastData.close);
    _accVolume += lastVolume;
    _accTypicalPriceWeighted += typicalPrice * lastVolume;

    double vwap = _accTypicalPriceWeighted/_accVolume;

    _data.push_back(vwap);
    _time.push_back((*barHistory)[0].time);
}

void VWAP::onRender() {
    ImPlot::SetNextLineStyle(_color,_lineWidth);
    ImPlot::PlotLine(_plotName.c_str(), _time.data(), _data.data(), _time.size());
}

void VWAP::onPopupRender() {

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void VWAP::reset() {
    Indicator::reset();
    _data.clear();
}

void VWAP::setupNewPeriod() {
    _accTypicalPriceWeighted = 0;
    _accVolume = 0;
}

const ImVec4 &VWAP::getColor() {
    return _color;
}

VWAP::~VWAP() {

}

double VWAP::calculateTypicalPrice(double low, double high, double close) {
    return (low + high + close) / 3;
}


bool VWAP::isNewPeriod(double timestamp, PeriodType period) {
    static time_t lastTimestamp;
    const time_t time = timestamp; //chrono::duration<double>(timestamp);

    auto lt = *std::localtime(&lastTimestamp);
    auto t = *std::localtime(&time);

    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;


    bool newPeriod = false;
    switch (period) {
        case Day:
            if (t.tm_year > lt.tm_year) {
                newPeriod = true;
            } else if (t.tm_year == lt.tm_year && t.tm_mon > lt.tm_mon) {
                newPeriod = true;
            } else if (t.tm_year == lt.tm_year && t.tm_mon == lt.tm_mon && t.tm_mday > lt.tm_mday) {
                newPeriod = true;
            }
        case Week:
            if (t.tm_year >= lt.tm_year) {
                newPeriod = true;
            } else if (t.tm_year == lt.tm_year && t.tm_mon > lt.tm_mon) {
                newPeriod = true;
            } else if (t.tm_year >= lt.tm_year && t.tm_mon >= lt.tm_mon && t.tm_mday >= lt.tm_mday &&
                       t.tm_wday <= lt.tm_wday) {
                newPeriod = true;
            }
        default:
            break;
    }


    if (newPeriod) {
        lastTimestamp = time;
        return true;
    } else {
        return false;
    }

}




