//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#ifndef BROKERAPP_PATHS_H
#define BROKERAPP_PATHS_H

#include <string>

class Paths {
public:
    //All the paths are relative to the binary so
    //TODO:: see how to solve cross platform paths
    inline static std::string ApiKeys = "../Resources/api_keys.json";
    inline static std::string UserData = "./DB/user_data.json";
    inline static std::string OrdersHistory = "./DB/order_history.json";
    inline static std::string OrdersOpened = "./DB/opened_orders.json";
};


#endif //BROKERAPP_PATHS_H
