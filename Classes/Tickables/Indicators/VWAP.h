//
// Created by Luiz Veloso on 18/01/22.
//

#ifndef INC_2021_12_AIBROKER_VWAP_H
#define INC_2021_12_AIBROKER_VWAP_H

#include "Indicator.h"

enum PeriodType {
    Day,
    Week,
    Month,
    Year
};


class VWAP : public Indicator,  public ReversedData<double>{
public:

    explicit VWAP(Ticker* ticker);
    ~VWAP();
    void calculate(BarHistory* barHistory) override;

    void onRender() override;
    void onPopupRender() override;
    void resetPlot() override;
    const ImVec4& getColor();

private:
    double _accVolume;
    double _accTypicalPriceWeighted;
    PeriodType _periodType = Day;
    void setupNewPeriod();
    bool isNewPeriod(double timestamp, PeriodType period);
    double calculateTypicalPrice(double low, double high, double close);
    std::vector<int> _lineIndexes;

    ImVec4 _color{1, 1, 1, 1};
    float _lineWidth = 2.0f;

};

#endif //INC_2021_12_AIBROKER_VWAP_H
