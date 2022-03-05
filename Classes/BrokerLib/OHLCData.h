//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_OHLCDATA_H
#define BROKERAPP_OHLCDATA_H

#include "IndicatorData.h"

class OHLCData : public IndicatorData<double, 4> {
public:
    explicit OHLCData(Ticker *ticker);

    ~OHLCData() = default;

    void calculate(BarHistory *barHistory) override;

};


#endif //BROKERAPP_OHLCDATA_H
