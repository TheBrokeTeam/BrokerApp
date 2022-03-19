//
// Created by Arthur Abel Motelevicz on 20/02/22.
//

#include "RestApiManager.h"
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <thread>
#include "LocalKeys.h"
#include "../../Helpers/Utils.h"
#include "../../Data/Order.h"

RestApiManager::RestApiManager() {
    _apictx = std::make_unique<boost::asio::io_context>();
    _api = std::make_unique<binapi::rest::api>(
            *_apictx
            ,"api.binance.com"
            ,"443"
            ,LocalKeys::privateKey // can be empty for non USER_DATA reqs
            ,LocalKeys::secretKey // can be empty for non USER_DATA reqs
            ,10000 // recvWindow milliseconds
    );
}

RestApiManager::~RestApiManager() {
    _api.reset(nullptr);
    _apictx->stop();
    _apictx.reset(nullptr);
}


void RestApiManager::getCandles(const Symbol &symbol,const CandlesCallback& callback) {
    _api->klines(symbol.getCode(),"1m",500,
                 [callback](const char *fl, int ec, std::string emsg, auto res) {
                     if ( ec ) {
                         std::cerr << "get price error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
                         return false;
                     }

                     std::cout << "Number of klines: " << res.klines.size() << std::endl;

                     //TODO:: make a parse
                     std::vector<TickData> data;
                     for(auto& k : res.klines)
                     {
                         TickData data_open;
                         TickData data_high;
                         TickData data_low;
                         TickData data_close;

                         //converting ms to sec and add simulated time for the sub tick on the bars
                         double startTimeMs = static_cast<double>(k.start_time);
                         double endTimeMs = static_cast<double>(k.end_time);

                         data_open.time  = startTimeMs;
                         data_high.time  = startTimeMs + 20000;// + duration*0.33;
                         data_low.time  = startTimeMs + 40000; // + duration*0.66;
                         data_close.time  = endTimeMs;

                         data_open.price = static_cast<double>(k.open);
                         data_high.price =  static_cast<double>(k.high);
                         data_low.price =  static_cast<double>(k.low);
                         data_close.price =  static_cast<double>(k.close);

                         //0.25 volume for each tick
                         double volume = static_cast<double>(k.volume)*0.25;
                         data_open.volume = volume;
                         data_high.volume = volume;
                         data_low.volume = volume;
                         data_close.volume = volume;

                         data.push_back(data_open);
                         data.push_back(data_high);
                         data.push_back(data_low);
                         data.push_back(data_close);
                     }

                     callback(data);
                     return true;
                 }
    );

    std::thread worker(&RestApiManager::runApiAsync, this);
    worker.detach();
}

void RestApiManager::runApiAsync() {
    std::cout << "Before run api" << std::endl;
    _apictx->restart();
    _apictx->run();
    std::cout << "After run api" << std::endl;
}


void RestApiManager::openOrder(const Symbol &symbol, const OrderCallback &callback) {

    _api->new_order(symbol.getCode(),
                    binapi::e_side::buy,
                    binapi::e_type::limit,
                    binapi::e_time::GTC,
                    binapi::e_trade_resp_type::FULL,
                    "0.004",
                    "2850.00",
                    "",
                    "",
                    "",
                    [callback](const char *fl, int ec, std::string emsg, auto res)
                    {
                        if ( ec ) {
                            std::cerr << "open order failed: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
                            return false;
                        }
                        std::cout << "open order success: " << res << std::endl;

                        Order order;
                        auto fullResp = res.get_responce_full();
                        order.symbol = fullResp.symbol;
                        order.orderId = fullResp.orderId;
                        order.clientOrderId = fullResp.clientOrderId;
                        order.transactTime = fullResp.transactTime;
                        order.price = static_cast<double>(fullResp.price);
                        order.origQty = static_cast<double>(fullResp.origQty);
                        order.executedQty = static_cast<double>(fullResp.executedQty);
                        order.cummulativeQuoteQty = static_cast<double>(fullResp.cummulativeQuoteQty);
                        order.status = fullResp.status;
                        order.timeInForce = fullResp.timeInForce;
                        order.type = fullResp.type;
                        order.side = fullResp.side;
                        std::vector<Order::fill_part> fillsVec;

                        for(binapi::rest::new_order_info_full_t::fill_part f : fullResp.fills) {
                            fillsVec.push_back({
                                                       static_cast<double>(f.price),
                                                       static_cast<double>(f.qty),
                                                       static_cast<double>(f.commission),
                                                       f.commissionAsset
                                               });
                        }

                        order.fills = fillsVec;

                        callback(order);
                        return true;
                    });


    std::thread worker(&RestApiManager::runApiAsync, this);
    worker.detach();
}

void RestApiManager::accountInfo()
{
    _api->account_info([](const char *fl, int ec, std::string emsg, auto res)
    {
        if ( ec ) {
            std::cerr << "get account info error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
            return false;
        }
        std::cout << "account info: " << res << std::endl;
        return true;
    });

    std::thread worker(&RestApiManager::runApiAsync, this);
    worker.detach();
}

void RestApiManager::startUserDataStream(UserDataStreamCallback callback) {
    auto start_uds = _api->start_user_data_stream([callback](const char *fl, int ec, std::string emsg, auto res)
    {
      if ( ec ) {
          std::cerr << "get user data stream error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
          callback(false,"");
          return false;
      }
      std::cout << "user data stream: " << res << std::endl;
      callback(true,res.listenKey);
      return true;
    });

    std::thread worker(&RestApiManager::runApiAsync, this);
    worker.detach();
}

void RestApiManager::cancelOrder(const Order& order) {
    auto start_uds = _api->cancel_order(order.symbol,order.orderId, order.clientOrderId,"",[](const char *fl, int ec, std::string emsg, auto res)
      {
          if ( ec ) {
              std::cerr << "cancelOrder error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
              return false;
          }
          std::cout << "cancelOrder: " << res << std::endl;
          return true;
      });

    std::thread worker(&RestApiManager::runApiAsync, this);
    worker.detach();
}




