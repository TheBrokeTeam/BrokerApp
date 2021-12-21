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

    if(!_context->getData().empty())
        loadTickable(tickable);
}

void Ticker::tick(const TickData &tickData)
{
    for(auto& t : _tickables){
        t->onTick(tickData);
    }
}

void Ticker::open(const TickData &tickData)
{
    for(auto& t : _tickables){
        t->onOpen(tickData);
    }
}

void Ticker::close(const TickData &tickData)
{
    for(auto& t : _tickables){
        t->onClose(tickData);
    }
}

void Ticker::reset()
{
    for(auto& t : _tickables){
        t->reset();
    }
}


void Ticker::loadTickable(Tickable *tickable)
{
    for (auto &d : _context->getData())
    {
        //loading the past candles - OHLC
        for(int i = 1; i <= 4; i++)
            updateTickerDataOnTickable(d,tickable,i);
    }
}

void Ticker::updateTickerDataOnTickable(const BarData& data, Tickable* tickable, int countTicks)
{
    TickData tickData;
    tickData.volume = data.volume;
    tickData.time = data.time;

    switch (countTicks) {
        case 1:
            tickData.price = data.open;
            tickable->onOpen(tickData);
            break;
        case 2:
            tickData.price = data.low;
            tickable->onTick(tickData);
            break;
        case 3:
            tickData.price = data.high;
            tickable->onTick(tickData);
            break;
        case 4:
            tickData.price = data.close;
            tickable->onClose(tickData);
        default:
            break;
    }
}

void Ticker::append(const TickData& data) {
    //TODO:: fazer agregação dos dados aqui baseado no time interval in minutes do symbol
    _data.insert(data);
}