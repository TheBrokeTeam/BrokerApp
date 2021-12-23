//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "iostream"
#include "Ticker.h"
#include "../Contexts/Context.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Tickables/Tickable.h"

Ticker::Ticker(Context *context,std::shared_ptr<Symbol> symbol): Contextualizable(context), _symbol(std::move(symbol)) {}

void Ticker::addTickable(Tickable *tickable)
{
    _tickables.push_back(tickable);
    //TODO:: passar aqui o bar history para nao precisar do methodo load tickable
//    tickable->onLoad(_symbol);
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

    //check if it is the open moment
    if(_barHistory.size() <= 0 || lastWasClosed){
        lastWasClosed = false;
        open(tickData);
        return;
    }

    //check if it is the close moment based on symbol
    long lastSecondOfCurrentBar = _barHistory[0].time + _symbol->getTimeIntervalInMinutes()*60 - 1;
    if(lastSecondOfCurrentBar <= (tickData.time)){
        lastWasClosed = true;
        close(tickData);
        return;
    }

    //normal tick update
    BarData data = _barHistory[0];

    data.volume += tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;

    _barHistory[0] = data;

    for(auto& t : _tickables){
        t->onTick(&_barHistory);
    }
}

void Ticker::close(const TickData& tickData) {
    BarData data = _barHistory[0];

    data.volume += tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;
    data.close = tickData.price;

    _barHistory[0] = data;

    for(auto& t : _tickables){
        t->onClose(&_barHistory);
    }
}

void Ticker::reset() {}

Symbol *Ticker::getSymbol() {
    return _symbol.get();
}
