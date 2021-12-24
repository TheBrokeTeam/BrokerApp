//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_SMA_H
#define BROKERAPP_SMA_H

#include "Indicator.h"

class SMA : public Indicator{
public:
    SMA(Ticker* ticker, int maSize);
    ~SMA();
    void calculate() override;
    void onLoad(BarHistory* barHistory) override;

private:
    int _averageSize = 3; // minimum size is 2
};


#endif //BROKERAPP_SMA_H
