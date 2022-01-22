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
    const  std::vector<double>& getOpenData();
    const  std::vector<double>& getHighData();
    const  std::vector<double>& getLowData();
    const  std::vector<double>& getCloseData();

    void updateLastBar(const BarData& barData);
    void clear();

private:
    std::vector<double> _time;
    std::vector<double> _volume;
    std::vector<double> _open;
    std::vector<double> _high;
    std::vector<double> _low;
    std::vector<double> _close;
};

#endif //BROKERAPP_BARHISTORY_H
