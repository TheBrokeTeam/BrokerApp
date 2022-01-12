//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Ticker.h"
#include "../Contexts/Context.h"
#include "../Tickables/Tickable.h"

Ticker::Ticker(Context *context,const Symbol& symbol): _symbol(symbol) {
    setContext(context);
    _id = uuid::generate_uuid_v4();
}

bool Ticker::removeTickable(Tickable *tickable)
{
//    for(auto it  = _indicators.begin(); it != _indicators.end(); it++) {
//        if (tickable == it->lock().get()) {
//            _indicators.erase(it);
//            return true;
//        }
//    }
//
//    for(auto it  = _strategies.begin(); it != _strategies.end(); it++) {
//        if (tickable == dynamic_cast<Tickable*>(*it)) {
//            _strategies.erase(it);
//            return true;
//        }
//    }

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
        if(auto tickable = t.lock())
            tickable->onTick(&_barHistory);
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
    long lastSecondOfCurrentBar = _barHistory[0].time + _symbol.getTimeIntervalInMinutes()*60 - 1;
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
        if(auto tickable = t.lock())
            tickable->onTick(&_barHistory);
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
        if(auto tickable = t.lock())
            tickable->onClose(&_barHistory);
    }

}

void Ticker::reset() {
    _barHistory.clear();
    lastWasClosed = false;
    
    for(auto& t : _tickables){
        if(auto tickable = t.lock())
            tickable->reset();
    }
}

Symbol *Ticker::getSymbol() {
    return &_symbol;
}

BarHistory *Ticker::getBarHistory() {
    return &_barHistory;
}

TickerId Ticker::getTickerId() {
    return _id;
}

//void Ticker::addIndicator(std::shared_ptr<Indicator> indicator) {
//    _indicators.push_back(indicator);
//    indicator->onLoad(&_barHistory);
//}
//
//void Ticker::addStrategy(Tickable *tickable) {
//    _strategies.push_back(dynamic_cast<Strategy*>(tickable));
//    tickable->onLoad(&_barHistory);
//}

void Ticker::addTickable(Tickable *tickable) {
    auto tickableAdded = _tickables.insert(tickable);
    (*tickableAdded.first)->onLoad(&_barHistory);
}
