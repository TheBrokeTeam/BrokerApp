//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKDATA_H
#define BROKERAPP_TICKDATA_H

#include <cstring>

struct TickData {
    double price;
    double volume;
    double time;
    TickData()    { Clear(); }
    void Clear()    { memset(this, 0, sizeof(*this)); }
};

#endif //BROKERAPP_TICKDATA_H
