//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Ticker.h"
#include "../Contexts/Context.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Tickables/Tickable.h"

Ticker::Ticker(Context *context,std::shared_ptr<Symbol> symbol):
_context(context),
_symbol(std::move(symbol)) {}

void Ticker::addTickable(Tickable *tickable)
{
    _tickables.push_back(tickable);
    tickable->onLoad(_symbol);

    if(!_data.empty())
        loadTickable(tickable);
}

void Ticker::open(const TickData& tickData) {
    BarData data;

    data.time = tickData.time;
    data.volume = tickData.volume;

    data.open = tickData.price;
    data.high = tickData.price;
    data.low = tickData.price;
    data.close = tickData.price;

    _barHistory.append(data);

    for(auto& t : _tickables){
        t->onOpen(&_barHistory);
    }
}

void Ticker::tick(const TickData& tickData) {
    BarData data = _barHistory[0];

    data.volume = tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;

    _barHistory[0] = data;

    for(auto& t : _tickables){
        t->onTick(&_barHistory);
    }
}

void Ticker::close(const TickData& tickData) {
    BarData data = _barHistory[0];

    data.volume = tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;
    data.close = tickData.price;

    _barHistory[0] = data;

    for(auto& t : _tickables){
        t->onClose(&_barHistory);
    }
}

void Ticker::reset() {}

void Ticker::append(const TickData& data) {
    _data.insert(data);
}