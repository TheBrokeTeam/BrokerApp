//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_STRATEGYROUTER_H
#define BROKERAPP_STRATEGYROUTER_H

#include <string>
#include "../APIRouter.h"

class StrategyRouter {
protected:
    std::string endpoint = "/strategy";
public:
    StrategyRouter();
    [[nodiscard]] APIRouter fetchByUserId(const std::string&) const;
    [[nodiscard]] APIRouter save(const rapidjson::Document& body) const;
    [[nodiscard]] APIRouter deleteById(const std::string&) const;
};


#endif //BROKERAPP_STRATEGYROUTER_H
