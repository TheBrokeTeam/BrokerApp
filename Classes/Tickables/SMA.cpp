//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "SMA.h"

SMA::SMA(Ticker *ticker, int maSize): Indicator(ticker) {
    _averageSize = maSize;

}

void SMA::calculate()
{
    if(_ys.empty())
        _ys.emplace_back(std::vector<double>());

    if(_barHistory->size() >= _averageSize)
    {
        double value = 0;
        for(int i = 0; i < _averageSize; i++)
            value += barHist[i].close;

        _ys[0].push_back(value/_averageSize);
        _time.push_back(time(0));
    }
}


SMA::~SMA() {}

void SMA::onLoad(BarHistory *barHistory) {
    Indicator::onLoad(barHistory);

    if(_ys.empty())
        _ys.emplace_back(std::vector<double>());

    auto& data = _barHistory->getData();

    if(data.size() >= _averageSize){
        for(int idx = _averageSize; idx < data.size(); idx++) {
            double value = 0;
            for (int i = 0; i < _averageSize; i++)
                value += data[idx - i].close;

            _ys[0].push_back(value / _averageSize);
            _time.push_back(data[idx].time);
        }
    }
}

