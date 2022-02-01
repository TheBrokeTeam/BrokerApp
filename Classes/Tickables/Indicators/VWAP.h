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

private:
    void resetVwap();
    double _accVolume;
    double _accTypicalPriceWeighted;
    PeriodType _periodType = Day;
    time_t _lastTimestamp = 0;

    void setupNewPeriod();
    bool isNewPeriod(double timestamp, PeriodType period);
    double calculateTypicalPrice(double low, double high, double close);
    std::vector<int> _lineIndexes;

    float _lineWidth = 2.0f;
    int _weekDayToReset = 0;
    double _weekTimeInSec = 24*60*60*7;


};

#endif //INC_2021_12_AIBROKER_VWAP_H
