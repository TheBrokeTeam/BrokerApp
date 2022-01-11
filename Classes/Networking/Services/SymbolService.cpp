//
// Created by Maykon Meneghel on 07/01/22.
//

#include "SymbolService.h"
#include "../Routes/SymbolRouter.h"
#include <string>

SymbolService::SymbolService() = default;


Json::Value SymbolService::fetchDataByCode(const std::string& code) {
    return this->apiManager.Request(SymbolRouter().getDataSymbol(code));
}

Json::Value SymbolService::fetchAllSymbols() {
    return this->apiManager.Request(SymbolRouter().getAllSymbols());
}