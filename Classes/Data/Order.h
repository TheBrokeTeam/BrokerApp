//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_ORDER_H
#define BROKERAPP_ORDER_H

#include <string>
#include <vector>
#include "Symbol.h"

class Order {
public:
    enum class OrderStatus{
        NEW,
        PARTIALLY_FILLED,
        FILLED,
        CANCELED,
        PENDING_CANCEL,
        REJECTED,
        EXPIRED
    };
    enum class OrderSide{
        BUY,
        SELL
    };

    enum class OrderType {
        LIMIT,
        MARKET
    };

    std::shared_ptr<Symbol> symbol{nullptr};
    OrderStatus status;
    OrderSide side;
    OrderType type;
    double reportTime;
    double transactionTime;
    std::string clientOrderId;
    double price;
    double origQty;
    double lastExecutedQty;
    double cumulativeQty;

    struct FillPart {
        double price;
        double qty;
        double commission;
        std::string commissionAsset;
    };
    std::vector<FillPart> fills;

    void updateOrder(const Order order){
        this->symbol = order.symbol;
        this->status = order.status;
//        this->side = order.side;
//        this->type = order.type;
        this->reportTime = order.reportTime;
//        this->transactionTime = order.transactionTime;
//        this->clientOrderId = order.clientOrderId;
        if(order.price != 0)
            this->price = order.price;
//        this->origQty = order.origQty;
        this->lastExecutedQty = order.lastExecutedQty;
        this->cumulativeQty = order.cumulativeQty;
    }


//    "e": "executionReport",        // Event type
//    "E": 1499405658658,            // Event time
//    "s": "ETHBTC",                 // Symbol
//    "c": "mUvoqJxFIILMdfAW5iGSOW", // Client order ID
//    "S": "BUY",                    // Side
//    "o": "LIMIT",                  // Order type
//    "f": "GTC",                    // Time in force
//    "q": "1.00000000",             // Order quantity
//    "p": "0.10264410",             // Order price
//    "P": "0.00000000",             // Stop price
//    "F": "0.00000000",             // Iceberg quantity
//    "g": -1,                       // OrderListId
//    "C": null,                     // Original client order ID; This is the ID of the order being canceled
//    "x": "NEW",                    // Current execution type
//    "X": "NEW",                    // Current order status
//    "r": "NONE",                   // Order reject reason; will be an error code.
//    "i": 4293153,                  // Order ID
//    "l": "0.00000000",             // Last executed quantity
//    "z": "0.00000000",             // Cumulative filled quantity
//    "L": "0.00000000",             // Last executed price
//    "n": "0",                      // Commission amount
//    "N": null,                     // Commission asset
//    "T": 1499405658657,            // Transaction time
//    "t": -1,                       // Trade ID
//    "I": 8641984,                  // Ignore
//    "w": true,                     // Is the order on the book?
//    "m": false,                    // Is this trade the maker side?
//    "M": false,                    // Ignore
//    "O": 1499405658657,            // Order creation time
//    "Z": "0.00000000",             // Cumulative quote asset transacted quantity
//    "Y": "0.00000000",              // Last quote asset transacted quantity (i.e. lastPrice * lastQty)
//    "Q": "0.00000000"              // Quote Order Qty
//    std::string symbol;
//    std::size_t orderId;
//    std::string clientOrderId;
//    double transactTime;
//    double price;
//    double origQty;
//    double executedQty;
//    double cummulativeQuoteQty;
//    std::string status;
//    std::string timeInForce;
//    std::string type;
//    std::string side;
//    struct fill_part {
//        double price;
//        double qty;
//        double commission;
//        std::string commissionAsset;
//    };
//    std::vector<fill_part> fills;
};


#endif //BROKERAPP_ORDER_H
