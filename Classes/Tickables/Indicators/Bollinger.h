//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_BOLLINGER_H
#define BROKERAPP_BOLLINGER_H


#include "Indicator.h"

class BollingerData{
public:
    double top;
    double mid;
    double bottom;
};

class Bollinger : public Indicator, public ReversedData<BollingerData> {
public:
    explicit Bollinger(Ticker* ticker);
    void calculate(BarHistory* barHistory) override;
    void reset() override;
    void onRender() override;
    int getAverageSize();
private:
    int _averageSize = 20;
};


#endif //BROKERAPP_BOLLINGER_H
