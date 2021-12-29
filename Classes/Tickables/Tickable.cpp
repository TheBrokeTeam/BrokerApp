//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Tickable.h"
#include <imgui_internal.h>

Tickable::Tickable(Ticker* ticker): _ticker(ticker){}

void Tickable::onOpen(BarHistory* barHistory) {
}

void Tickable::onTick(BarHistory* barHistory) {
}

void Tickable::onClose(BarHistory* barHistory) {
}

void Tickable::onLoad(BarHistory *barHistory) {
}

void Tickable::reset() {

}
