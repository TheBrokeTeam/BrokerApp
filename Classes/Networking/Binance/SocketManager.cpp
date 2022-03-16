//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketManager.h"
#include <iostream>
#include <boost/asio/io_context.hpp>
#include <thread>

SocketManager::SocketManager() {

    _ioctx = std::make_unique<boost::asio::io_context>();
    _ioCandlectx = std::make_unique<boost::asio::io_context>();

    _ws = std::make_unique<binapi::ws::websockets>(
            *_ioctx
            ,"stream.binance.com"
            ,"9443"
   );

    _candleWs = std::make_unique<binapi::ws::websockets>(
            *_ioCandlectx
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
    _handler = nullptr;
}

void SocketManager::startStreamAsync() {
    std::cout << "Before run" << std::endl;
    _ioctx->restart();
    _ioctx->run();
    std::cout << "After run" << std::endl;
}

void SocketManager::openCandleStream(const Symbol &symbol, const SocketManager::CandlesCallback &callback) {
    _candleHandler = _candleWs->klines(symbol.getCode().c_str(),"1m",
                          [callback](const char *fl, int ec, std::string emsg, auto kline) {
                              if ( ec ) {
                                  std::cerr << "subscribe trades error: fl=" << fl << ", ec=" << ec << ", emsg=" << emsg << std::endl;
                                  return false;
                              }
                              std::vector<TickData> data;

                              TickData data_open;
                              TickData data_high;
                              TickData data_low;
                              TickData data_close;

                              //converting ms to sec and add simulated time for the sub tick on the bars
                              double timeMs = static_cast<double>(kline.t);
                              double duration = static_cast<double>(kline.T - kline.t);

                              data_open.time  = timeMs;
                              data_high.time  = timeMs + duration*0.33;
                              data_low.time  = timeMs + duration*0.66;
                              data_close.time  = timeMs + duration - 1;

                              data_open.price = static_cast<double>(kline.o);
                              data_high.price =  static_cast<double>(kline.h);
                              data_low.price =  static_cast<double>(kline.l);
                              data_close.price =  static_cast<double>(kline.c);

                              //0.25 volume for each tick
                              double volume = static_cast<double>(kline.v)*0.25;
                              data_open.volume = volume;
                              data_high.volume = volume;
                              data_low.volume = volume;
                              data_close.volume = volume;

                              data.push_back(data_open);
                              data.push_back(data_high);
                              data.push_back(data_low);
                              data.push_back(data_close);

                              callback(data);
                              return true;
                          }
    );

    std::thread worker(&SocketManager::startCandleStreamAsync, this);
    worker.detach();
}

void SocketManager::closeCandleStream(const Symbol &symbol) {
    _ioCandlectx->stop();
    _candleWs->unsubscribe(_candleHandler);
    _candleHandler = nullptr;
}

void SocketManager::startCandleStreamAsync() {
    std::cout << "Before run" << std::endl;
    _ioCandlectx->restart();
    _ioCandlectx->run();
    std::cout << "After run" << std::endl;
}






