//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Ticker.h"
#include "../Contexts/Context.h"

Ticker::Ticker(Context *context){
    setContext(context);
    _id = uuid::generate_uuid_v4();
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

    //calculations to make interval slots
    double interval = _symbol.getTimeIntervalInMiliSeconds();
    double remaining = std::fmod(tickData.time,interval);
    double intervalFloor = tickData.time - remaining;

    if (remaining > 0)
        std::cout << "Remaining: " << remaining << " Base: " << intervalFloor <<std::endl;

    data.time_ms = intervalFloor;
    data.time_s = data.time_ms/1000;

    data.volume = tickData.volume;

    data.open = tickData.price;
    data.high = tickData.price;
    data.low = tickData.price;
    data.close = tickData.price;

    _barHistory.append(data);

    for(auto& t : _tickables){
        t->onTick(&_barHistory);
    }

    _lastIntervalFloor = intervalFloor;
}

void Ticker::tick(const TickData& tickData, bool isLiveTick) {

    const std::lock_guard<std::mutex> lock(_tickMutex);

    if(isLiveTick){
        liveTick(tickData);
        return;
    }

    //check if it is the open moment
    if(_barHistory.size() <= 0 || lastWasClosed){
        lastWasClosed = false;
        open(tickData);
        return;
    }

    //check if it is the close moment based on symbol interval (open time + bar's duration)
    double barTime = _barHistory(0,BarDataType::TIME_MS);
    double lastTimeOfCurrentBar = barTime + _symbol.getTimeIntervalInMiliSeconds() - 1;

    if(lastTimeOfCurrentBar <= (tickData.time)){
        lastWasClosed = true;
        close(tickData);
        return;
    }

    //it's just an update tick
    updateTick(tickData);

    for(auto& t : _tickables){
        t->onTick(&_barHistory);
    }
}

void Ticker::liveTick(const TickData &tickData) {
    //check if it is the open moment
    if(_barHistory.size() <= 0 || lastWasLiveClosed){
        lastWasLiveClosed = false;
        open(tickData);
        return;
    }

    //normal tick update
    double interval = _symbol.getTimeIntervalInMiliSeconds();
    double remaining = std::fmod(tickData.time,interval);
    double intervalFloor = tickData.time - remaining;

    if(intervalFloor > _lastIntervalFloor){
        lastWasLiveClosed = true;
        close(tickData);
        return;
    }

    updateTick(tickData);
}


void Ticker::close(const TickData& tickData) {
    BarData data;

    data.time_ms = _barHistory(0,BarDataType::TIME_MS);
    data.time_s = _barHistory(0,BarDataType::TIME_S);
    data.open = _barHistory(0,BarDataType::OPEN);
    data.high = _barHistory(0,BarDataType::HIGH);
    data.low = _barHistory(0,BarDataType::LOW);
    data.close = _barHistory(0,BarDataType::CLOSE);
    data.volume = _barHistory(0,BarDataType::VOLUME);

    data.volume += tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;;
    data.close = tickData.price;

    _barHistory.updateLastBar(data);

    for(auto& t : _tickables){
            t->onClose(&_barHistory);
    }

}

void Ticker::reset() {
    _barHistory.clear();
    lastWasClosed = false;
    
    for(auto& t : _tickables)
        t->reset();
}

Symbol* Ticker::getSymbol() {
    return &_symbol;
}

BarHistory* Ticker::getBarHistory() {
    return &_barHistory;
}

TickerId Ticker::getTickerId() {
    return _id;
}

void Ticker::addTickable(Tickable *tickable) {

    const bool is_in = _tickables.find(tickable) != _tickables.end();
    if(is_in) return;

    auto tickableAdded = _tickables.insert(tickable);
    (*tickableAdded.first)->onLoad(&_barHistory);
}

void Ticker::setSymbol(const Symbol &symbol) {
    _symbol = symbol;
    _zoomOutMax = _symbol.getTimeIntervalInSeconds()*_maxBarsToRender;
}

double Ticker::getZoomOutMax() {
    return _zoomOutMax;
}

int Ticker::getMaxBarsToRender() {
    return _maxBarsToRender;
}

void Ticker::updateTick(const TickData &tickData)
{
    //normal tick update
    BarData data;

    data.time_ms = _barHistory(0,BarDataType::TIME_MS);
    data.time_s = _barHistory(0,BarDataType::TIME_S);
    data.open = _barHistory(0,BarDataType::OPEN);
    data.high = _barHistory(0,BarDataType::HIGH);
    data.low = _barHistory(0,BarDataType::LOW);
    data.close = _barHistory(0,BarDataType::CLOSE);
    data.volume = _barHistory(0,BarDataType::VOLUME);

    data.volume += tickData.volume;
    data.high = tickData.price > data.high ? tickData.price : data.high;
    data.low = tickData.price < data.low ? tickData.price : data.low;
    data.close = tickData.price;

    _barHistory.updateLastBar(data);

}

