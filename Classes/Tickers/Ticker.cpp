//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Ticker.h"
#include "../Contexts/Context.h"
#include "../Tickables/Tickable.h"

Ticker::Ticker(Context *context,std::shared_ptr<Symbol> symbol): _symbol(std::move(symbol)) {
    setContext(context);
}

void Ticker::addTickable(Tickable *tickable)
{
    _tickables.push_back(tickable);
    tickable->onLoad(&_barHistory);
}

bool Ticker::removeTickable(Tickable *tickable)
{
    for(auto it  = _tickables.begin(); it != _tickables.end(); it++) {
        if (tickable == (*it)) {
            _tickables.erase(it);
            return true;
        }
    }
    return false;
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

    //check if it is the close moment based on symbol interval
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

    _barHistory.updateLasBar(data);

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

    _barHistory.updateLasBar(data);

    for(auto& t : _tickables){
        t->onClose(&_barHistory);
    }
}

void Ticker::reset() {
    _barHistory.clear();
    lastWasClosed = false;
    for(auto& t : _tickables){
        t->reset();
    }
}

Symbol *Ticker::getSymbol() {
    return _symbol.get();
}

BarHistory *Ticker::getBarHistory() {
    return &_barHistory;
}
