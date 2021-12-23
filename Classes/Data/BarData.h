//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BARDATA_H
#define BROKERAPP_BARDATA_H

#include <cstring>

struct BarData {
public:
    double time;
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
