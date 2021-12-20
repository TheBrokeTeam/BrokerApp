//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Ticker.h"
#include "../Contexts/Context.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"


Ticker::Ticker(Context *context,std::shared_ptr<Symbol> symbol): _context(context),_symbol(std::move(symbol)) {

}

void Ticker::addTickable(Tickable *tickable)
{
    _tickables.insert(tickable);
//    tickable->onLoad(_setup);

    if(!_context->getData().empty())
        loadTickable(tickable);

}

void Ticker::tick(const TickData &tickData)
{
    for(auto& t : _tickables){
//        t->onTick(tickData);
    }
}

void Ticker::open(const TickData &tickData)
{
    for(auto& t : _tickables){
//        t->onOpen(tickData);
    }
}

void Ticker::close(const TickData &tickData)
{
    for(auto& t : _tickables){
//        t->onClose(tickData);
    }
}

void Ticker::reset()
{
    _currentIndex = 0;
    _currentTime = 0;
    _countTicks = 0;

    for(auto& t : _tickables){
//        t->reset();
    }
}


void Ticker::loadTickable(Tickable *tickable)
{
    for (auto &d : _context->getData())
    {
        //loading the past candles - OHLC
        for(int i = 1; i <= 4; i++)
        {
//            updateTickerDataOnTickable(d,tickable,i);
        }
    }
}

void Ticker::update(TickData data) {

    //TODO:: fazer agregação dos dados aqui baseado no time interval in inutes
//    _symbol->getTimeIntervalInMinutes();

//    switch (countTicks) {
//        case 1:
//            tickData.price = data.open;
////            tickable->onOpen(tickData);
//            break;
//        case 2:
//            tickData.price = data.low;
////            tickable->onTick(tickData);
//            break;
//        case 3:
//            tickData.price = data.high;
////            tickable->onTick(tickData);
//            break;
//        case 4:
//            tickData.price = data.close;
////            tickable->onClose(tickData);
//        default:
//            break;
//    }
}


