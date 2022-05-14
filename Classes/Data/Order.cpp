//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Order.h"
#include "../Common/Json/BAJson.h"
#include "../Networking/API/Services/OrderService.h"
#include <utility>

Order::Order(int id, std::string code, std::string clientOrderId, std::size_t transactTime, double price, double origQty,
             double executedQty, double cummulativeQuoteQty, OrderStatusType status, std::string timeInForce,
             OrderType type, TradeSideType side) {

    this->id = id;
    this->code = std::move(code);
    this->clientOrderId = std::move(clientOrderId);
    this->transactTime = transactTime;
    this->price = price;
    this->origQty = origQty;
    this->executedQty = executedQty;
    this->cummulativeQuoteQty = cummulativeQuoteQty;
    this->status = status;
    this->timeInForce = std::move(timeInForce);
    this->type = type;
    this->side = side;
//    this->createdBy = std::move(createdBy);
//    this->updatedAt = std::move(updatedAt);
//    this->createdAt = std::move(createdAt);
}

rapidjson::Document Order::toJson() {
    rapidjson::Document jsonOrder = BAJson::document();

    BAJson::set(jsonOrder, "code", this->code);
    BAJson::set(jsonOrder, "clientOrderId", this->clientOrderId);
    BAJson::set(jsonOrder, "createdBy", this->createdBy);

    BAJson::set(jsonOrder, "transactTime", double(this->transactTime));
    BAJson::set(jsonOrder, "price", this->price);
    BAJson::set(jsonOrder, "origQty", this->origQty);
    BAJson::set(jsonOrder, "executedQty", this->executedQty);
    BAJson::set(jsonOrder, "cummulativeQuoteQty", this->cummulativeQuoteQty);

    BAJson::set(jsonOrder, "status", Order::statusTypeToString(this->status));
    BAJson::set(jsonOrder, "timeInForce", this->timeInForce);
    BAJson::set(jsonOrder, "type", Order::typeToString(this->type));
    BAJson::set(jsonOrder, "side", Order::tradeSideTypeToString(this->side));

    rapidjson::Document jsonFillArray;
    jsonFillArray.StartArray();
    for(auto& fill: fills) {
        auto n = fill.toJson();
        BAJson::append(jsonFillArray, n);
    }

    BAJson::set(jsonOrder, "fills", jsonFillArray);

    return jsonOrder;
}

Order Order::Parse(const rapidjson::Value& doc) {
    assert(doc.IsObject());

    Order order = Order(atoi(doc["id"].GetString()),
                        doc["code"].GetString(),
                        doc["clientOrderId"].GetString(),
                        std::size_t(doc["transactTime"].GetDouble()),
                        doc["price"].GetDouble(),
                        doc["origQty"].GetDouble(),
                        doc["executedQty"].GetDouble(),
                        doc["cummulativeQuoteQty"].GetDouble(),
                        Order::stringToStatusType(doc["status"].GetString()),
                        doc["timeInForce"].GetString(),
                        Order::stringToType(doc["type"].GetString()),
                        Order::stringToTradeSideType(doc["side"].GetString())
                        );

    std::vector<fill_part> fills;
    for(auto& jsonFill: doc["fills"].GetArray()) {
        auto n = fill_part::Parse(jsonFill);
        fills.push_back(n);
    }

    order.setFills(fills);

    return order;
}

void Order::Save() {
    OrderService orderService;
    orderService.createOrder(this->toJson());
}

std::string Order::statusTypeToString(OrderStatusType value) {
    switch (value) {
        case OrderStatusType::Cancelled:           { return "Cancelled";       }
        case OrderStatusType::Expired:             { return "Expired";         }
        case OrderStatusType::Filled:              { return "Filled";          }
        case OrderStatusType::PartiallyFilled:     { return "PartiallyFilled"; }
    }
}

void Order::setFills(const std::vector<fill_part>& fillsVec) {
    this->fills = fillsVec;
}

std::string Order::getCode() {
    return this->code;
}

int Order::getId() {
    return this->id;
}

std::string Order::getClientId() {
    return this->clientOrderId;
}

OrderStatusType Order::stringToStatusType(const std::string& value) {
    if ( value == "Cancelled" ) return OrderStatusType::Cancelled;
    if ( value == "Expired" ) return OrderStatusType::Expired;
    if ( value == "Filled" ) return OrderStatusType::Filled;
    if ( value == "PartiallyFilled" ) return OrderStatusType::PartiallyFilled;
}

std::string Order::typeToString(OrderType value) {
    switch (value) {
        case OrderType::Limit:      { return "Limit";     }
        case OrderType::LimitStop:  { return "LimitStop"; }
        case OrderType::Market:     { return "Market";    }
        case OrderType::OCO:        { return "OCO";       }
    }
}

OrderType Order::stringToType(const std::string& value) {
    if ( value == "Limit" )     return OrderType::Limit;
    if ( value == "LimitStop" ) return OrderType::LimitStop;
    if ( value == "Market" )    return OrderType::Market;
    if ( value == "OCO" )       return OrderType::OCO;
}

std::string Order::tradeSideTypeToString(TradeSideType value) {
    switch (value) {
        case TradeSideType::Buy:        { return "Buy";       }
        case TradeSideType::Sell:       { return "Sell";      }
        case TradeSideType::Undefined:  { return "Undefined"; }
    }
}

TradeSideType Order::stringToTradeSideType(const std::string &value) {
    if ( value == "Buy" )  return TradeSideType::Buy;
    if ( value == "Sell" ) return TradeSideType::Sell;
    else return TradeSideType::Undefined;
}

double Order::getPrice() const {
    return price;
}

double Order::getOrigQty() const {
    return origQty;
}

double Order::getExecutedQty() const {
    return executedQty;
}

double Order::getCummulativeQuoteQty() const {
    return cummulativeQuoteQty;
}

OrderStatusType Order::getStatus() const {
    return status;
}

OrderType Order::getType() const {
    return type;
}

TradeSideType Order::getSide() const {
    return side;
}

const std::vector<fill_part> &Order::getFills() const {
    return fills;
}

const std::string &Order::getCreatedAt() const {
    return createdAt;
}

rapidjson::Document fill_part::toJson() {
    rapidjson::Document jsonFill = BAJson::document();
    BAJson::set(jsonFill, "price", this->price);
    BAJson::set(jsonFill, "qty", this->qty);
    BAJson::set(jsonFill, "commission", this->commission);
    BAJson::set(jsonFill, "commissionAsset", this->commissionAsset);
    return jsonFill;
}

fill_part fill_part::Parse(const rapidjson::Value& doc) {
    return {
        doc["price"].GetDouble(),
        doc["qty"].GetDouble(),
        doc["commission"].GetDouble(),
        doc["commissionAsset"].GetString()
    };
}