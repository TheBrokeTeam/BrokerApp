//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_VOLUMEDATA_H
#define BROKERAPP_VOLUMEDATA_H


#include "IndicatorData.h"

class VolumeData : public IndicatorData<double> {
public:
    explicit VolumeData(Ticker *ticker);

    ~VolumeData() = default;

    void calculate(BarHistory *barHistory) override;

};



#endif //BROKERAPP_VOLUMEDATA_H
