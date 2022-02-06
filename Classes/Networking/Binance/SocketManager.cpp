//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketManager.h"
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <thread>

binance::SocketManager::SocketManager() {

    _ioctx = std::make_unique<boost::asio::io_context>();
   _ws = std::make_unique<binapi::ws::websockets>(
            *_ioctx
            ,"stream.binance.com"
            ,"9443"
   );


}


binance::SocketManager::~SocketManager() {

}

void binance::SocketManager::openStream() {

//    if(!_ioctx->stopped()){
//        closeStream();
//    }

    _handler = _ws->trade("ETHUSDT",
                                    [](const char *fl, int ec, std::string emsg, auto trades) {
                                        if ( ec ) {
                                            std::cerr << "subscribe trades error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;

                                            return false;
                                        }

                                        std::cout << "trades: " << trades << std::endl;

                                        return true;
                                    }
    );

    std::thread worker(&binance::SocketManager::startStreamAsync, this);
    worker.detach();
}

void binance::SocketManager::closeStream() {
    _ioctx->stop();
    _ws->unsubscribe(_handler);
}

void binance::SocketManager::startStreamAsync() {
    std::cout << "Before run" << std::endl;
    _ioctx->restart();
    _ioctx->run();
    std::cout << "After run" << std::endl;
}






