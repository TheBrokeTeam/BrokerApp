//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_SOCKETMANAGER_H
#define BROKERAPP_SOCKETMANAGER_H

#include <memory>
#include <binapi/api.hpp>
#include <binapi/websocket.hpp>
#include "../../Data/Symbol.h"

class SocketManager {
    public:
    typedef std::function<void(const TickData& data)> StreamCallback;
    typedef std::function<void(std::vector<TickData>& data)> CandlesCallback;

    SocketManager();
    ~SocketManager();
    void openStream(const Symbol& symbol, const StreamCallback& callback);
    void closeStream(const Symbol& symbol);
    void openCandleStream(const Symbol& symbol, const CandlesCallback& callback);
    void closeCandleStream(const Symbol& symbol);


private:
    void startStreamAsync();
    void startCandleStreamAsync();

    std::unique_ptr<boost::asio::io_context> _ioctx{nullptr};
    std::unique_ptr<boost::asio::io_context> _ioCandlectx{nullptr};

    std::unique_ptr<binapi::ws::websockets> _ws{nullptr};
    std::unique_ptr<binapi::ws::websockets> _candleWs{nullptr};

    binapi::ws::websockets::handle _handler{nullptr};

    binapi::ws::websockets::handle _candleHandler{nullptr};


};

#endif //BROKERAPP_SOCKETMANAGER_H
