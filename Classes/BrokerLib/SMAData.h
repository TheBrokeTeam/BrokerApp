//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERAPP_SMADATA_H
#define BROKERAPP_SMADATA_H

#include "IndicatorData.h"

class SMAData : public IndicatorData<double>{
public:
    explicit SMAData(Ticker* ticker);
    ~SMAData() = default;
    void calculate(BarHistory* barHistory) override;
    void setAverageSize(int size);
    int getAverageSize() const;

private:
    int _averageSize = 12; // minimum size is 1
};



#endif //BROKERAPP_SMADATA_H
