//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketManager.h"
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <thread>

SocketManager::SocketManager() {

    _ioctx = std::make_unique<boost::asio::io_context>();
   _ws = std::make_unique<binapi::ws::websockets>(
            *_ioctx
            ,"stream.binance.com"
            ,"9443"
   );
}

SocketManager::~SocketManager() {}

void SocketManager::openStream(const Symbol& symbol,const StreamCallback& callback) {
    _handler = _ws->trade(symbol.getCode().c_str(),
                                    [callback](const char *fl, int ec, std::string emsg, auto trades) {
                                        if ( ec ) {
                                            std::cerr << "subscribe trades error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
                                            return false;
                                        }
//                                        std::cout << "trades: " << trades << std::endl;
                                        TickData data;
                                        data.time = static_cast<double>(trades.E);
                                        data.volume = static_cast<double>(trades.q);
                                        data.price = static_cast<double>(trades.p);
                                        callback(data);
                                        return true;
                                    }
    );

    std::thread worker(&SocketManager::startStreamAsync, this);
    worker.detach();
}

void SocketManager::closeStream(const Symbol& symbol) {
    _ioctx->stop();
    _ws->unsubscribe(_handler);
}

void SocketManager::startStreamAsync() {
    std::cout << "Before run" << std::endl;
    _ioctx->restart();
    _ioctx->run();
    std::cout << "After run" << std::endl;
}






