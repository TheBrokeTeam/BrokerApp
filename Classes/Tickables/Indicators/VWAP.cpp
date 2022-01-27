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
    if (isNewPeriod((*barHistory)(0,BarDataType::TIME), _periodType)) {
        setupNewPeriod();
    }

    double lastVolume = (*barHistory)(0,BarDataType::VOLUME);
    double typicalPrice = calculateTypicalPrice((*barHistory)(0,BarDataType::LOW),
                                                (*barHistory)(0,BarDataType::HIGH),
                                                (*barHistory)(0,BarDataType::CLOSE));

    _accVolume += lastVolume;
    _accTypicalPriceWeighted += typicalPrice * lastVolume;

    double vwap = _accTypicalPriceWeighted/_accVolume;

    insert(vwap);
    _time.push_back((*barHistory)(0,BarDataType::TIME));
}

void VWAP::onRender() {
    for(int i = 0 ; i < _lineIndexes.size(); i++) {
        ImPlot::SetNextLineStyle(_color, _lineWidth);
        if(i == 0)
            ImPlot::PlotLine(_plotName.c_str(), &_time[0], &getData()[0], _lineIndexes[0]);
        else
            ImPlot::PlotLine(_plotName.c_str(), &_time[_lineIndexes[i-1]], &getData()[_lineIndexes[i-1]], _lineIndexes[i] - _lineIndexes[i-1]);
    }
}

void VWAP::onPopupRender() {
    const char* items[] = { "Day","Week", "Month", "Year"  };
    static int item_current = 0;
    if (ImGui::Combo("Period", &item_current, items, IM_ARRAYSIZE(items))) {
        _periodType = static_cast<PeriodType>(item_current);
        resetVwap();
    }

    if(_periodType == Week){
        const char* weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
        if (ImGui::Combo("Week day to reset", &_weekDayToReset, weekdays, IM_ARRAYSIZE(weekdays))) {
            resetVwap();
        }
    }

    ImGui::ColorEdit4("Color",&_color.x);
    ImGui::Separator();
    ImGui::SliderFloat("Thickness", &_lineWidth, 0, 5);
}

void VWAP::resetPlot() {
    Indicator::resetPlot();
    setupNewPeriod();
    _lineIndexes.clear();
    clear();
    _lastTimestamp = 0;
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
    const time_t time = timestamp; //chrono::duration<double>(timestamp);

    auto lt = *std::localtime(&_lastTimestamp);
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
        case Week: {
            double deltaTime = time - _lastTimestamp;
            if(t.tm_wday == _weekDayToReset && deltaTime >= _weekTimeInSec)
                newPeriod = true;
        }
            break;
        default:
            break;
    }

    if (newPeriod) {
        _lastTimestamp = time;
        if(!_time.empty()) {
            _lineIndexes.push_back(_time.size());
        }
        return true;
    } else {
        return false;
    }

}

void VWAP::resetVwap() {
    resetPlot();
    onLoad(_ticker->getBarHistory());
}




