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

class Tickable;
class BarData;
class Symbol;
struct TickData;
class Context;

class Ticker {
public:
    Ticker(Context* context,std::shared_ptr<Symbol> symbol);
    virtual ~Ticker() = default;
    void addTickable(Tickable* tickable);
    virtual void append(const TickData& data);
    void updateTickerDataOnTickable(const BarData& data, Tickable* tickable, int countTicks);


private:
    void reset();
    void loadTickable(Tickable* tickable);

    void tick(const TickData &tickData);
    void open(const TickData &tickData);
    void close(const TickData &tickData);

    //hold all the tickables
    std::vector<Tickable*> _tickables;
    Context* _context{nullptr};

    //to save loaded data
    std::set<TickData> _data;

    std::shared_ptr<Symbol> _symbol{nullptr};
};



#endif //BROKERAPP_TICKER_H
