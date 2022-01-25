//
// Created by Luiz Veloso on 11/01/22.
//

#ifndef BROKERAPP_WMA_H
#define BROKERAPP_WMA_H

#include "Indicator.h"

class WMA : public Indicator,  public ReversedData<double>{
public:
    explicit WMA(Ticker* ticker);
    ~WMA();
    void calculate(BarHistory* barHistory) override;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;
    const ImVec4& getColor();

private:
    int _averageSize = 5; // must be >= 1
    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
    int sumNfirst(int number);

};


#endif //BROKERAPP_WMA_H
