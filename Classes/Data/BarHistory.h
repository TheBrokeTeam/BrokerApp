//
// Created by Arthur Abel Motelevicz on 21/12/21.
//

#ifndef BROKERAPP_BARHISTORY_H
#define BROKERAPP_BARHISTORY_H

#include <vector>
#include "BarData.h"
#include "ReversedData.h"

class BarHistory : public ReversedData<BarData>{
public:
    void append(const BarData& data);
    const std::vector<BarData>& getData();
    int size();
    const  std::vector<double>& getTimeData();
    const  std::vector<double>& getVolumeData();
    void updateLasBar(const BarData& barData);
    void clear();

private:
    std::vector<double> _time;
    std::vector<double> _volume;


};

#endif //BROKERAPP_BARHISTORY_H
