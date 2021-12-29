//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#include "Bollinger.h"

#include <implot.h>
#include <implot_internal.h>

Bollinger::Bollinger (Ticker *ticker): Indicator(ticker) {
    setName("BOLL");
}

void Bollinger::calculate(BarHistory* barHistory)
{
    if((*barHistory).size() >= _avarageSize) {

        //calculate the mean of the last <averagesize>
        double mean = 0;
        double den = 1.0 / _avarageSize;
        for (int i = 0; i < _avarageSize; ++i)
            mean += (*barHistory)[i].close * den;

        //calulate the standard deviation of this
        double den2 = 1.0 / (_avarageSize - 1.0);
        double x   = 0;
        for (int i = 0; i < _avarageSize; ++i)
            x += ((*barHistory)[i].close - mean) * ((*barHistory)[i].close - mean) * den2;

        double stdv = sqrt(x);

        _bollinger_top.push_back(mean + 2 * stdv);

        //use the data as the mid bollinger line
        _data.push_back(mean);

        _bollinger_bot.push_back(mean - 2 * stdv);
        _time.push_back((*barHistory)[0].time);
    }
}

void Bollinger::reset() {
    Indicator::reset();
    _bollinger_bot.clear();
    _bollinger_top.clear();
}

void Bollinger::render() {

    //safe check
    if(_data.empty()) return;

//    ImPlot::SetNextLineStyle(_color,_lineWidth);
//    ImPlot::PlotLine(_name.c_str(), _time.data(), _data.data(), _time.size());

    ImPlot::SetNextFillStyle(ImVec4(0.5,0.5,1,1),0.25f);
    ImPlot::PlotShaded(_name.c_str(),_time.data(),_bollinger_top.data(),_bollinger_bot.data(),_data.size());
    ImPlot::SetNextLineStyle(ImVec4(0.5,0.5,1,1));

}

Bollinger::~Bollinger() {}

