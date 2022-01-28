//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#include <iostream>
#include "BarHistory.h"

void BarHistory::append(const BarData &data) {
    push(data.time, BarDataType::TIME);
    push(data.open, BarDataType::OPEN);
    push(data.high, BarDataType::HIGH);
    push(data.low, BarDataType::LOW);
    push(data.close, BarDataType::CLOSE);
    push(data.volume, BarDataType::VOLUME);
}

void BarHistory::updateLastBar(const BarData &barData) {

    getData(BarDataType::TIME).back() = barData.time;
    getData(BarDataType::OPEN).back() = barData.open;
    getData(BarDataType::HIGH).back() = barData.high;
    getData(BarDataType::LOW).back() = barData.low;
    getData(BarDataType::CLOSE).back() = barData.close;
    getData(BarDataType::VOLUME).back() = barData.volume;
}

BarData BarHistory::getBarDataAt(int idx) {
    BarData d;
    d.time = getData(BarDataType::TIME)[idx];
    d.open = getData(BarDataType::OPEN)[idx];
    d.high = getData(BarDataType::HIGH)[idx];
    d.low = getData(BarDataType::LOW)[idx];
    d.close = getData(BarDataType::CLOSE)[idx];
    d.volume = getData(BarDataType::VOLUME)[idx];
    return d;
}

