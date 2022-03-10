//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_DATAMANAGER_H
#define BROKERAPP_DATAMANAGER_H

#include <iostream>
#include "../BrokerLib/OHLCData.h"

class Ticker;

class DataManager {

public:
    OHLCData* createOLHCData(Ticker* ticker);
    bool clearOHLCData(Ticker* ticker);
private:
    std::map<Ticker*,OHLCData> _ohlcData;

};


#endif //BROKERAPP_DATAMANAGER_H
