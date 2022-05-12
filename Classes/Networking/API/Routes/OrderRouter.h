//
// Created by Maykon Meneghel on 12/05/22.
//

#ifndef BROKERAPP_ORDERROUTER_H
#define BROKERAPP_ORDERROUTER_H

#include <string>
#include "../APIRouter.h"

class OrderRouter {
protected:
    std::string endpoint = "/router";
public:
    OrderRouter();
    [[nodiscard]] APIRouter fetchByUserId(const std::string&) const;
    [[nodiscard]] APIRouter createOrder(const rapidjson::Document& body) const;
    [[nodiscard]] APIRouter deleteById(const std::string&) const;
};


#endif //BROKERAPP_ORDERROUTER_H
