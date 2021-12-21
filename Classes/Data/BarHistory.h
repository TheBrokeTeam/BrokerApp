//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#ifndef BROKERAPP_BARHISTORY_H
#define BROKERAPP_BARHISTORY_H

#include <set>
#include "BarData.h"

class BarHistory {
public:
    BarData &operator[](int reversedIndex);
    void append(const BarData& data);
    const std::set<BarData>& getData();
    int size();

private:
    std::set<BarData> _barData;
    int fixedIndex(int reversedIndex);

}
#endif //BROKERAPP_BARHISTORY_H
