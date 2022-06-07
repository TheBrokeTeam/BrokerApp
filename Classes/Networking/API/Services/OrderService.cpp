//
// Created by Maykon Meneghel on 12/05/22.
//

#include "OrderService.h"
#include "../Routes/OrderRouter.h"

rapidjson::Document OrderService::createOrder(const rapidjson::Document &order) {
    return this->apiManager.Request(OrderRouter().createOrder(order));
}

rapidjson::Document OrderService::deleteOrder(const std::string &id) {
    return this->apiManager.Request(OrderRouter().deleteById(id));
}

rapidjson::Document OrderService::fetchOrders(const std::string &userId) {
    return this->apiManager.Request(OrderRouter().fetchByUserId(userId));
}

OrderService::OrderService() {

}
