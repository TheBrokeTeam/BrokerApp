//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKER_H
#define BROKERAPP_TICKER_H

//#include "../Data/OHLC.h"
//#include "../Managers/Tickable.h"
//#include <set>
//#include "../Events/UIEvents.h"
#include <set>
#include <vector>
#include "../Data/BarHistory.h"
#include "../Contexts/Contextualizable.h"

class Tickable;
class BarData;
class Symbol;
struct TickData;

class Ticker : public Contextualizable{
public:
    Ticker(Context* context, std::shared_ptr<Symbol> symbol);
    virtual ~Ticker() = default;
    void addTickable(Tickable* tickable);

    void tick(const TickData &tickData);
    Symbol* getSymbol();

    BarHistory* getBarHistory();

private:
    void reset();
    void open(const TickData &tickData);
    void close(const TickData &tickData);

    bool lastWasClosed = false;

    //hold all the tickables
    std::vector<Tickable*> _tickables;

    //to save loaded data
    BarHistory _barHistory;

    std::shared_ptr<Symbol> _symbol{nullptr};

};



#endif //BROKERAPP_TICKER_H
