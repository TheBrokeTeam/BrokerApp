//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#ifndef BROKERAPP_BARHISTORY_H
#define BROKERAPP_BARHISTORY_H

#include <vector>
#include "BarData.h"
#include "ReversedData.h"
class BarHistory : public ReversedData<double,6>{
public:
    void append(const BarData& data);
    void updateLastBar(const BarData& barData);
    BarData getBarDataAt(int idx);

};

#endif //BROKERAPP_BARHISTORY_H
