//
// Created by Luiz Veloso on 06/01/22.
//

#ifndef BROKERAPP_EMA_H
#define BROKERAPP_EMA_H

#include "Indicator.h"

class EMA : public Indicator,  public ReversedData<double>{
public:
    explicit EMA(Ticker* ticker);
    void calculate(BarHistory* barHistory) override;
    void setAverageSize(int size);
    int getAverageSize() const;
    void setSmothingSize(int size);
    int getSmothingSize() const;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;


private:
    int _smothingSize = 2; // must be <= 1 + _averageSize... it's almost always 2.
    int _averageSize = 5; // must be >= 1
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
};



#endif //BROKERAPP_EMA_H
