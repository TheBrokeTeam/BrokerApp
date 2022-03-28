//
// Created by Arthur Abel Motelevicz on 27/03/22.
//

#ifndef BROKERAPP_BINANCEPARSER_H
#define BROKERAPP_BINANCEPARSER_H

#include <binapi/api.hpp>
#include <binapi/websocket.hpp>
#include "../../Data/Order.h"

class BinanceParser{
public:

    //ORDERS
    inline static std::shared_ptr<Order> apiNewOrderParse(const binapi::rest::new_order_info_full_t &fullResp) {

        std::shared_ptr<Order> order = std::make_shared<Order>();
        order->symbol = std::make_shared<Symbol>(fullResp.symbol);
        order->clientOrderId = fullResp.clientOrderId;
        order->transactionTime = static_cast<double>(fullResp.transactTime);
        order->price = static_cast<double>(fullResp.price);
        order->origQty = static_cast<double>(fullResp.origQty);
        order->lastExecutedQty = static_cast<double>(fullResp.executedQty);
        order->cumulativeQty = static_cast<double>(fullResp.cummulativeQuoteQty);
        order->status = statusFromString(fullResp.status);
        order->type = typeFromString(fullResp.type);
        order->side = sideFromString(fullResp.side);
        std::vector<Order::FillPart> fillsVec;

        for (binapi::rest::new_order_info_full_t::fill_part f : fullResp.fills) {
            fillsVec.push_back({
                                       static_cast<double>(f.price),
                                       static_cast<double>(f.qty),
                                       static_cast<double>(f.commission),
                                       f.commissionAsset
                               });
        }

        order->fills = fillsVec;

        return std::move(order);
    }

    //https://github.com/binance/binance-spot-api-docs/blob/master/user-data-stream.md#order-update
    inline static Order socketUpdateOrderParse(const binapi::userdata::order_update_t &msg) {

        Order order;
        order.reportTime = static_cast<double>(msg.E);
        order.symbol = std::make_shared<Symbol>(msg.s);
        order.clientOrderId = msg.c;
        order.transactionTime = static_cast<double>(msg.T);

        //for market orders
        order.price += static_cast<double>(msg.L);

        order.origQty = static_cast<double>(msg.q);
        order.lastExecutedQty = static_cast<double>(msg.l);
        order.cumulativeQty = static_cast<double>(msg.z);
        order.status = statusFromString(msg.X);
        order.type = typeFromString(msg.o);
        order.side = sideFromString(msg.S);

        return order;
    }

    inline static binapi::e_type toOrderType(Order::OrderType ot) {
        binapi::e_type type;
        switch (ot) {
            case Order::OrderType::MARKET:
                type = binapi::e_type::market;
                break;
            case Order::OrderType::LIMIT:
            default:
                type = binapi::e_type::limit;
                break;
        }
        return type;
    }

    inline static Order::OrderType fromOrderType(binapi::e_type ot) {
        Order::OrderType type;
        switch (ot) {
            case binapi::e_type::market:
                type = Order::OrderType::MARKET;
                break;
            case binapi::e_type::limit:
            default:
                type = Order::OrderType::LIMIT;
                break;
        }
        return type;
    }


    inline static binapi::e_side toOrderSide(Order::OrderSide os) {
        binapi::e_side side;
        switch (os) {
            case Order::OrderSide::SELL:
                side = binapi::e_side::sell;
                break;
            case Order::OrderSide::BUY:
            default:
                side = binapi::e_side::buy;
                break;
        }
        return side;
    }

    inline static Order::OrderSide fromOrderSide(binapi::e_side os) {
        Order::OrderSide side;
        switch (os) {
            case binapi::e_side::sell:
                side = Order::OrderSide::SELL;
                break;
            case binapi::e_side::buy:
            default:
                side = Order::OrderSide::BUY;
                break;
        }
        return side;
    }


    inline static Order::OrderStatus statusFromString(const std::string& strStatus){
        if(strStatus == "NEW") return Order::OrderStatus::NEW;
        if(strStatus == "PARTIALLY_FILLED") return Order::OrderStatus::PARTIALLY_FILLED;
        if(strStatus == "FILLED") return Order::OrderStatus::FILLED;
        if(strStatus == "CANCELED") return Order::OrderStatus::CANCELED;
        if(strStatus == "EXPIRED") return Order::OrderStatus::EXPIRED;
        if(strStatus == "PENDING_CANCEL") return Order::OrderStatus::PENDING_CANCEL;
        if(strStatus == "REJECTED") return Order::OrderStatus::REJECTED;
    }

    inline static Order::OrderType typeFromString(const std::string& strType){
        if(strType == "LIMIT") return Order::OrderType::LIMIT;
        if(strType == "MARKET") return Order::OrderType::MARKET;
    }

    inline static Order::OrderSide sideFromString(const std::string& strSide){
        if(strSide == "BUY") return Order::OrderSide::BUY;
        if(strSide == "SELL") return Order::OrderSide::SELL;
    }

    //END ORDERS

};

#endif //BROKERAPP_BINANCEPARSER_H
