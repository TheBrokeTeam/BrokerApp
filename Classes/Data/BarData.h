//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BARDATA_H
#define BROKERAPP_BARDATA_H

#include <cstring>

enum BarDataType{
    TIME_MS,
    TIME_S,
    OPEN,
    HIGH,
    LOW,
    CLOSE,
    VOLUME
};

struct BarData {
public:
    double time_ms;
    double time_s;
    double open;
    double high;
    double low;
    double close;
    double volume;
    // Functions
    BarData()    { Clear(); }
    void Clear()    { memset(this, 0, sizeof(*this)); }
};


#endif //BROKERAPP_BARDATA_H
