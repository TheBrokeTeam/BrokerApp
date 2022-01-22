//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#include <iostream>
#include "BarHistory.h"

void BarHistory::append(const BarData &data) {
    _data.push_back(data);

    _time.push_back(data.time);
    _volume.push_back(data.volume);

    _open.push_back(data.open);
    _high.push_back(data.high);
    _low.push_back(data.low);
    _close.push_back(data.close);
}

const std::vector<BarData>& BarHistory::getData(){
    return _data;
}

const std::vector<double> &BarHistory::getTimeData() {
    return _time;
}

const std::vector<double> &BarHistory::getVolumeData() {
    return _volume;
}
const std::vector<double> &BarHistory::getOpenData() {
    return _open;
}

const std::vector<double> &BarHistory::getHighData() {
    return _high;
}

const std::vector<double> &BarHistory::getLowData() {
    return _low;
}

const std::vector<double> &BarHistory::getCloseData() {
    return _close;
}

void BarHistory::clear() {
    _data.clear();
    _time.clear();
    _volume.clear();

    _open.clear();
    _high.clear();
    _close.clear();
    _low.clear();
}

void BarHistory::updateLastBar(const BarData &barData) {
    _data[_data.size() - 1]= barData;
    _volume[_volume.size() - 1] = barData.volume;

    _open.back() = barData.open;
    _high.back() = barData.high;
    _low.back() = barData.low;
    _close.back() = barData.close;
}

int BarHistory::size() {
    return _data.size();
}

