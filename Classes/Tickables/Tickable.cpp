//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Tickable.h"
#include <imgui_internal.h>

void Tickable::onOpen(const TickData& tickData) {
    BarData data;

    data.time = tickData.time;
    data.volume = tickData.volume;

    data.open = tickData.price;
    data.high = tickData.price;
    data.low = tickData.price;
    data.close = tickData.price;

    _data.push_back(data);
}

void Tickable::onTick(const TickData& tickData) {
    BarData data = _data[_currentIndex];

    data.volume = tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;

    _data[_currentIndex] = data;
}

void Tickable::onClose(const TickData& tickData) {
    BarData data = _data[_currentIndex];

    data.volume = tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;
    data.close = tickData.price;

    _data[_currentIndex] = data;

    _currentIndex++;
}

void Tickable::onLoad(std::shared_ptr<Symbol> symbol) {
    _symbol = std::move(symbol);
}

void Tickable::reset() {
    _data.clear();
    _currentIndex = 0;
}

double Tickable::time(int indexBar) {
    return _data[(fixedIndex(indexBar))].time;
}

double Tickable::volume(int indexBar) {
    return _data[(fixedIndex(indexBar))].volume;;
}

double Tickable::open(int indexBar) {
    return _data[(fixedIndex(indexBar))].open;
}

double Tickable::high(int indexBar) {
    return _data[(fixedIndex(indexBar))].high;
}

double Tickable::low(int indexBar) {
    return _data[(fixedIndex(indexBar))].low;
}

double Tickable::close(int indexBar) {
    return _data[(fixedIndex(indexBar))].close;
}

int Tickable::fixedIndex(int reversedIndex) {
    int fixedIndex = ImMax<int>(0,_data.size() - 1 - reversedIndex);
    fixedIndex = ImMin<int>(fixedIndex,_data.size() - 1);
    return fixedIndex;
}

int Tickable::size() {
    return _data.size();
}
