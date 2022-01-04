//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_SMA_H
#define BROKERAPP_SMA_H

#include "Indicator.h"

class SMA : public Indicator,  public ReversedData<double>{
public:
    explicit SMA(Ticker* ticker);
    void calculate(BarHistory* barHistory) override;
    void setAverageSize(int size);
    int getAverageSize() const;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;

private:
    int _averageSize = 12; // minimum size is 1
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
};


#endif //BROKERAPP_SMA_H
