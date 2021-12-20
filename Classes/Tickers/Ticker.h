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

    void update(TickData data);


private:
    void reset();
    void loadTickable(Tickable* tickable);

    void tick(const TickData &tickData);
    void open(const TickData &tickData);
    void close(const TickData &tickData);

    //hold all the tickables
    std::set<Tickable*> _tickables;

    Context* _context{nullptr};

    //to save loaded data
//    BarData _data;
    std::shared_ptr<Symbol> _symbol{nullptr};

    // for simulation data
    void updateTickerData(const BarData& data);
    int _countTicks = 0;
    bool _simulating = false;
    int _currentIndex = -1;
    float _timeToTick = 0.5f; //sec
    float _currentTime = 0;
    float _speed = 1.0f;
};



#endif //BROKERAPP_TICKER_H
