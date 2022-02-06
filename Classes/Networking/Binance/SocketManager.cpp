//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketManager.h"
#include <iostream>
#include <binapi/api.hpp>
#include <binapi/websocket.hpp>

#include <boost/asio/io_context.hpp>
#include <boost/asio/steady_timer.hpp>

binance::SocketManager::SocketManager() {

}

binance::SocketManager::~SocketManager() {

}

void binance::SocketManager::openStream() {
    boost::asio::io_context ioctx;

    binapi::ws::websockets ws{
            ioctx
            ,"stream.binance.com"
            ,"9443"
    };

    auto trade_handler = ws.trade("ETHUSDT",
                                  [](const char *fl, int ec, std::string emsg, auto trades) {
                                      if ( ec ) {
                                          std::cerr << "subscribe trades error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                                          return false;
                                      }

                                      std::cout << "trades: " << trades << std::endl;

                                      return true;
                                  }
    );

    boost::asio::steady_timer timer0{ioctx, std::chrono::steady_clock::now() + std::chrono::seconds(10)};
    timer0.async_wait([&ws, trade_handler](const auto &/*ec*/){
        std::cout << "unsubscribing trade_handler: " << trade_handler << std::endl;
        ws.unsubscribe(trade_handler);
    });

    ioctx.run();
}
