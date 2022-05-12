//
// Created by Maykon Meneghel on 12/05/22.
//

#ifndef BROKERAPP_ORDERSERVICE_H
#define BROKERAPP_ORDERSERVICE_H

#include "../APIManager.h"
#include <rapidjson/document.h>
#include <string>

class OrderService {
private:
    APIManager apiManager = APIManager();

public:
    OrderService();
    rapidjson::Document createOrder(const rapidjson::Document &order);
    rapidjson::Document deleteOrder(const std::string &id);
    rapidjson::Document fetchOrders(const std::string &userId);
};


#endif //BROKERAPP_ORDERSERVICE_H
