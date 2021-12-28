//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_SMA_H
#define BROKERAPP_SMA_H

#include "Indicator.h"

class SMA : public Indicator{
public:
    SMA(Ticker* ticker);
    ~SMA();
    void calculate(BarHistory* barHistory) override;
    void render() override;

private:
    int _averageSize = 2; // minimum size is 2
};


#endif //BROKERAPP_SMA_H
