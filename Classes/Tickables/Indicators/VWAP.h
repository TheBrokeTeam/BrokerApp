//
// Created by Luiz Veloso on 18/01/22.
//

#ifndef INC_2021_12_AIBROKER_VWAP_H
#define INC_2021_12_AIBROKER_VWAP_H

#include "Indicator.h"

class VWAP : public Indicator,  public ReversedData<double>{
public:
    explicit VWAP(Ticker* ticker);
    ~VWAP();
    void calculate(BarHistory* barHistory) override;

    void onRender() override;
    void onPopupRender() override;
    void reset() override;
    const ImVec4& getColor();

private:
    double _accVolume;
    double _accTypicalPriceWeighted;
    void setupNewDay();

    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;
};

#endif //INC_2021_12_AIBROKER_VWAP_H
