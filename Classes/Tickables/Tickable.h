//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKABLE_H
#define BROKERAPP_TICKABLE_H

#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Data/BarHistory.h"
#include "../Tickers/Ticker.h"

#define barHist (*_barHistory)

class Tickable {
public:
    Tickable(Ticker* ticker);
    virtual ~Tickable();
    virtual void onOpen(BarHistory* barHistory);
    virtual void onClose(BarHistory* barHistory);
    virtual void onTick(BarHistory* barHistory);
    void setPriority(int priority);
    int getPriority();
    virtual void reset();

    virtual void onLoad(BarHistory* barHistory);
    bool operator < (const Tickable& rhs){ rhs._priority > _priority;}

protected:
    Ticker* _ticker{nullptr};
    BarHistory* _barHistory{nullptr};
private:
    int _priority = 0;
};


#endif //BROKERAPP_TICKABLE_H
