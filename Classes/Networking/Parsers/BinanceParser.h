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
    inline static std::shared_ptr<Order> apiNewOrderParse(const binapi::rest::new_order_info_full_t &fullResp) {

        std::shared_ptr<Order> order = std::make_shared<Order>();
        order->symbol = fullResp.symbol;
        order->clientOrderId = fullResp.clientOrderId;
        order->transactionTime = static_cast<double>(fullResp.transactTime);
        order->price = static_cast<double>(fullResp.price);
        order->origQty = static_cast<double>(fullResp.origQty);
        order->lastExecutedQty = static_cast<double>(fullResp.executedQty);
        order->cumulativeQty = static_cast<double>(fullResp.cummulativeQuoteQty);
        order->setStatus(fullResp.status);
        order->setType(fullResp.type);
        order->setSide(fullResp.side);
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

    


};

#endif //BROKERAPP_BINANCEPARSER_H
