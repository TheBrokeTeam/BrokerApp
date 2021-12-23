//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#include <iostream>
#include "BarHistory.h"

BarData& BarHistory::operator[](int reversedIndex) {
    auto it = _barData.begin();
    std::advance(it, fixedIndex(reversedIndex));
    return const_cast<BarData&>(*it);
}

int BarHistory::fixedIndex(int reversedIndex) {
    int fixedIndex = std::max<int>(0,_barData.size() - 1 - reversedIndex);
    fixedIndex = std::min<int>(fixedIndex,_barData.size() - 1);
    return fixedIndex;
}

void BarHistory::append(const BarData &data) {
    _barData.push_back(data);
}

const std::vector<BarData>& BarHistory::getData(){
    return _barData;
}

int BarHistory::size() {
    return _barData.size();
}
