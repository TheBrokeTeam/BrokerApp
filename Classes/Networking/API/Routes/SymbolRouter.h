//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_SYMBOLROUTER_H
#define UNTITLED1_SYMBOLROUTER_H


#include "../APIRouter.h"
#include <string>

class SymbolRouter {
protected:
    std::string endpoint = "/symbols";
public:
    SymbolRouter();
    [[nodiscard]] APIRouter getDataSymbol(const std::string &code) const;
    [[nodiscard]] APIRouter getAllSymbols() const;
};

#endif //UNTITLED1_SYMBOLROUTER_H
