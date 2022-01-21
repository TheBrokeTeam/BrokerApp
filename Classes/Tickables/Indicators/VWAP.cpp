//
// Created by Luiz Veloso on 18/01/22.
//

#include "VWAP.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "../../Tickers/Ticker.h"

using namespace std;


VWAP::VWAP(Ticker *ticker): Indicator(ticker) {
    setPlotName("VWAP");
}

void VWAP::calculate(BarHistory* barHistory)
{
    if (isNewPeriod((*barHistory)[0].time, _periodType)) {
        setupNewPeriod();
    }

    double lastVolume = (*barHistory)[0].volume;
    double typicalPrice = calculateTypicalPrice((*barHistory)[0].low, (*barHistory)[0].high, (*barHistory)[0].close);

    _accVolume += lastVolume;
    _accTypicalPriceWeighted += typicalPrice * lastVolume;

    double vwap = _accTypicalPriceWeighted/_accVolume;

    _data.push_back(vwap);
    _time.push_back((*barHistory)[0].time);
}

void VWAP::onRender() {
    for(int i = 0 ; i < _lineIndexes.size(); i++) {
        ImPlot::SetNextLineStyle(_color, _lineWidth);
        if(i == 0)
            ImPlot::PlotLine(_plotName.c_str(), &_time[0], &_data[0], _lineIndexes[0]);
        else
            ImPlot::PlotLine(_plotName.c_str(), &_time[_lineIndexes[i-1]], &_data[_lineIndexes[i-1]], _lineIndexes[i] - _lineIndexes[i-1]);
    }
}

void VWAP::onPopupRender() {
    const char* items[] = { "Day","Week", "Month", "Year"  };
    static int item_current = 0;
    if (ImGui::Combo("Period", &item_current, items, IM_ARRAYSIZE(items))) {
        _periodType = static_cast<PeriodType>(item_current);
        resetPlot();
        onLoad(_ticker->getBarHistory());
    }

    ImGui::ColorEdit4("Color",{&_color.x});
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void VWAP::resetPlot() {
    Indicator::resetPlot();
    setupNewPeriod();
    _lineIndexes.clear();
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
    static time_t lastTimestamp; // add valor
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
            break;
        case Year:
            if (t.tm_year > lt.tm_year) {
                newPeriod = true;
            }
            break;
        case Month:
            if (t.tm_year >= lt.tm_year && t.tm_mon > lt.tm_mon) {
                newPeriod = true;
            }
            break;
        case Week:
            //
//            if (t.tm_year >= lt.tm_year) {
//                newPeriod = true;
//            } else if (t.tm_year == lt.tm_year && t.tm_mon > lt.tm_mon) {
//                newPeriod = true;
//            } else if (t.tm_year >= lt.tm_year && t.tm_mon >= lt.tm_mon && t.tm_mday >= lt.tm_mday &&
//                       t.tm_wday <= lt.tm_wday) {
//                newPeriod = true;
//            }
            break;
        default:
            break;
    }



    if (newPeriod) {
        lastTimestamp = time;
        if(_time.size() > 0)
            _lineIndexes.push_back(_time.size());
        return true;
    } else {
        return false;
    }

}




