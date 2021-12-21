//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Tickable.h"
#include <imgui_internal.h>

Tickable::Tickable(Context *context,std::shared_ptr<Symbol> symbol):
_context(context),
_symbol(std::move(symbol)) {}

void Tickable::onLoad(std::shared_ptr<Symbol> symbol) {
    _symbol = std::move(symbol);
}

void Tickable::onOpen(BarHistory* barHistory) {}

void Tickable::onTick(BarHistory* barHistory) {}

void Tickable::onClose(BarHistory* barHistory) {}
