//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#include <iostream>
#include "BarHistory.h"

void BarHistory::append(const BarData &data) {
    _data.push_back(data);
    _time.push_back(data.time);
    _volume.push_back(data.volume);
}

const std::vector<BarData>& BarHistory::getData(){
    return _data;
}

int BarHistory::size() {
    return _data.size();
}

const std::vector<double> &BarHistory::getTimeData() {
    return _time;
}

const std::vector<double> &BarHistory::getVolumeData() {
    return _volume;
}

void BarHistory::clear() {
    _data.clear();
    _time.clear();
    _volume.clear();
}

void BarHistory::updateLasBar(const BarData &barData) { //todo: rename
    _data[_data.size() - 1]= barData;
    _volume[_volume.size() - 1] = barData.volume;
}
