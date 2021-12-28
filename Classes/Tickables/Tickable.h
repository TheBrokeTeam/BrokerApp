//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKABLE_H
#define BROKERAPP_TICKABLE_H

#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Data/BarHistory.h"
#include "../Contexts/Contextualizable.h"
#include "../Tickers/Ticker.h"

#define barHist (*_barHistory)

class Tickable {
public:
    Tickable(Ticker* ticker);
    virtual void onOpen(BarHistory* barHistory);
    virtual void onClose(BarHistory* barHistory);
    virtual void onTick(BarHistory* barHistory);

    virtual void onLoad(BarHistory* barHistory);

    virtual void reset();


protected:
    Ticker* _ticker{nullptr};
    BarHistory* _barHistory{nullptr};
};


#endif //BROKERAPP_TICKABLE_H
