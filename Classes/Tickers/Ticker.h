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
#include "../Data/Symbol.h"
#include "../Contexts/Contextualizable.h"
#include "../Tickables/Tickable.h"

class BarData;
class Indicator;
class Strategy;
struct TickData;

struct TickableComparison
{
    bool operator () (Tickable* lhs, Tickable* rhs) const  {
        return  lhs->getPriority() <= rhs->getPriority();
    }
};

typedef const std::string& TickerId;

class Ticker : public Contextualizable{
public:
    Ticker(Context* context);
    virtual ~Ticker() = default;

    void reset();
    void addTickable(Tickable* tickable);
    bool removeTickable(Tickable *tickable);

    void tick(const TickData &tickData);

    void setSymbol(const Symbol& symbol);
    Symbol* getSymbol();
    BarHistory* getBarHistory();
    TickerId getTickerId();

private:
    void open(const TickData &tickData);
    void close(const TickData &tickData);

    bool lastWasClosed = false;

    std::set<Tickable*,TickableComparison> _tickables;

    //to save loaded data
    BarHistory _barHistory;

    Symbol _symbol{""};

    std::string _id;
    bool _shouldRender = false;
};



#endif //BROKERAPP_TICKER_H
