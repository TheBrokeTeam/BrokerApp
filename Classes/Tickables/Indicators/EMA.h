//
// Created by Luiz Veloso on 06/01/22.
//

#ifndef BROKERAPP_EMA_H
#define BROKERAPP_EMA_H

#include "Indicator.h"

class EMA : public Indicator,  public ReversedData<double>{
public:
    explicit EMA(Ticker* ticker);
    ~EMA();
    void calculate(BarHistory* barHistory) override;
    void setAverageSize(int size);
    int getAverageSize() const;

    void onRender() override;
    void onPopupRender() override;
    void resetPlot() override;

private:
    int _smoothingSize = 2; // must be <= 1 + _averageSize... it's almost always 2.
    int _averageSize = 14; // must be >= 1
    float _lineWidth = 2.0f;
};



#endif //BROKERAPP_EMA_H
