//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_BOLLINGER_H
#define BROKERAPP_BOLLINGER_H


#include "Indicator.h"

enum BollingerDataType{
    TOP,
    MID,
    BOTTOM
};

class Bollinger : public Indicator, public ReversedData<double,3> {
public:
    explicit Bollinger(Ticker* ticker);
    void calculate(BarHistory* barHistory) override;
    void resetPlot() override;
    void onRender() override;
    int getAverageSize() const;

private:
    int _averageSize = 20;

};


#endif //BROKERAPP_BOLLINGER_H
