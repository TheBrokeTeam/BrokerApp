//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_ORDER_H
#define BROKERAPP_ORDER_H

#include <string>
#include <vector>
#include <rapidjson/document.h>

enum OrderType {
    Limit,
    LimitStop,
    Market,
    OCO
};

enum TradeSideType {
    Buy,
    Sell,
    Undefined
};

enum OrderStatusType {
    Cancelled,
    Expired,
    Filled,
    PartiallyFilled,
};

struct fill_part {
    double price;
    double qty;
    double commission;
    std::string commissionAsset;
    [[nodiscard]] rapidjson::Document toJson();
    static fill_part Parse(const rapidjson::Value&);
};

class Order {
private:
    int id;
    std::string code;
    std::string clientOrderId;
    std::size_t transactTime;
    double price;
    double origQty{};
    double executedQty;
    double cummulativeQuoteQty;
    OrderStatusType status;
    std::string timeInForce;
    OrderType type;
    TradeSideType side;
    std::vector<fill_part> fills{};
    std::string createdBy;
    std::string updatedAt;
    std::string createdAt;

public:
    Order(int id, std::string code, std::string clientOrderId, std::size_t transactTime, double price, double origQty,
          double executedQty, double cummulativeQuoteQty, OrderStatusType status, std::string timeInForce,
          OrderType type, TradeSideType side);

    std::string GetCode();
    int GetId();
    std::string GetClientId();

    void setFills(const std::vector<fill_part>& fillsVec);
    rapidjson::Document toJson();
    static Order Parse(const rapidjson::Document&);
    void Save();

    static std::string statusTypeToString(OrderStatusType value);
    static OrderStatusType stringToStatusType(const std::string& value);

    static std::string typeToString(OrderType value);
    static OrderType stringToType(const std::string& value);

    static std::string tradeSideTypeToString(TradeSideType value);
    static TradeSideType stringToTradeSideType(const std::string& value);
};


#endif //BROKERAPP_ORDER_H
