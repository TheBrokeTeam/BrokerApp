//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_CONTEXT_H
#define BROKERAPP_CONTEXT_H

#include <vector>
#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Tickers/Ticker.h"

class Context {
public:
        virtual Ticker* loadSymbol(const Symbol& symbol) = 0;
        virtual void loadTicker(const Symbol &symbol) = 0;

private:
    std::vector<TickData> _data;
};

#endif //BROKERAPP_CONTEXT_H
