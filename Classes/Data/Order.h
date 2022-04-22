//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_ORDER_H
#define BROKERAPP_ORDER_H

#include <string>
#include <vector>

class Order {
public:
    std::string symbol;
    std::size_t orderId;
    std::string clientOrderId;
    std::size_t transactTime;
    double price;
    double origQty;
    double executedQty;
    double cummulativeQuoteQty;
    std::string status;
    std::string timeInForce;
    std::string type;
    std::string side;
    struct fill_part {
        double price;
        double qty;
        double commission;
        std::string commissionAsset;
    };
    std::vector<fill_part> fills;
};


#endif //BROKERAPP_ORDER_H
