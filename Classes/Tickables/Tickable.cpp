//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Tickable.h"

Tickable::Tickable(Ticker* ticker): _ticker(ticker){}

void Tickable::onOpen(BarHistory* barHistory) {
    _barHistory = barHistory;
}

void Tickable::onTick(BarHistory* barHistory) {
    _barHistory = barHistory;
}

void Tickable::onClose(BarHistory* barHistory) {
    _barHistory = barHistory;
}

void Tickable::onLoad(BarHistory *barHistory) {
    _barHistory = barHistory;
}

void Tickable::reset() {}
