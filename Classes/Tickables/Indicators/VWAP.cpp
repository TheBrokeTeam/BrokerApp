//
// Created by Luiz Veloso on 18/01/22.
//

#include "VWAP.h"
#include <ctime>
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

    push(vwap);
    _time.push_back((*barHistory)(0,BarDataType::TIME));
}

void VWAP::onRender() {
    auto renderInfo = getRenderInfo(_ticker);
    for(int i = 0 ; i < _lineIndexes.size(); i+= 2) {
        ImPlot::SetNextLineStyle(_color, _lineWidth);
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
    //add first line indexes
    _lineIndexes.push_back(0);
    _lineIndexes.push_back(0);

    clear();
    _lastTimestamp = 0;
}

void VWAP::setupNewPeriod() {
    _accTypicalPriceWeighted = 0;
    _accVolume = 0;
}

VWAP::~VWAP() {}

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
            _lineIndexes.push_back(_time.size());
        }
        return true;
    } else {
        _lineIndexes.back() = _time.size();
        return false;
    }

}

void VWAP::resetVwap() {
    resetPlot();
    onLoad(_ticker->getBarHistory());
}




