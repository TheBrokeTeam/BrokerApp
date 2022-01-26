//
// Created by Maykon Meneghel on 07/01/22.
//

#include "SymbolRouter.h"
#include <string>

SymbolRouter::SymbolRouter() = default;

APIRouter SymbolRouter::getDataSymbol(const std::string& code) const {
    return {get, this->endpoint + "?code=" + code};
}

APIRouter SymbolRouter::getAllSymbols() const {
    return {get, this->endpoint + "/all"};
}