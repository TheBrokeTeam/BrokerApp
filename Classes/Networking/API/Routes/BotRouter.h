//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_BOTROUTER_H
#define BROKERAPP_BOTROUTER_H

#include <string>
#include "../APIRouter.h"

class BotRouter {
protected:
    std::string endpoint = "/bot";
public:
    BotRouter();
    [[nodiscard]] APIRouter fetchByUserId(const std::string&) const;
    [[nodiscard]] APIRouter save(const rapidjson::Document& body) const;
    [[nodiscard]] APIRouter deleteById(const std::string&) const;
};


#endif //BROKERAPP_BOTROUTER_H
