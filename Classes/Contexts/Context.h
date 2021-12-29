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
        virtual void update(float dt);
        virtual void startSimulation(Ticker* ticker) = 0;
        virtual void setSimulationSpeed(float speed) = 0;
        virtual bool isSimulating()  = 0;
};

#endif //BROKERAPP_CONTEXT_H
