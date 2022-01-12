//
// Created by Maykon Meneghel on 07/01/22.
//

#include "SymbolService.h"
#include "../Routes/SymbolRouter.h"
#include <string>

SymbolService::SymbolService() = default;


rapidjson::Document SymbolService::fetchDataByCode(const std::string& code) {
    return this->apiManager.Request(SymbolRouter().getDataSymbol(code));
}

rapidjson::Document SymbolService::fetchAllSymbols() {
    return this->apiManager.Request(SymbolRouter().getAllSymbols());
}