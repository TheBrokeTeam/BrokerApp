//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "DataManager.h"
#include "../Tickers/Ticker.h"

OHLCData *DataManager::createOLHCData(Ticker* ticker) {
    OHLCData ohlc = OHLCData(ticker);
    _ohlcData.insert(std::pair<Ticker*,OHLCData>(ticker,ohlc));

    ticker->addTickable(&_ohlcData.at(ticker));
    return &_ohlcData.at(ticker);
}

bool DataManager::clearOHLCData(Ticker *ticker) {
    if(_ohlcData.count(ticker)){
        _ohlcData.at(ticker).clear();
        return true;
    }
     return false;
}
