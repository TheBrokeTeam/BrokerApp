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

    SocketManager();
    ~SocketManager();
    void openStream(const Symbol& symbol, const StreamCallback& callback);
    void closeStream(const Symbol& symbol);

    void startStreamAsync();

private:
    std::unique_ptr<boost::asio::io_context> _ioctx{nullptr};
    std::unique_ptr<binapi::ws::websockets> _ws{nullptr};
    binapi::ws::websockets::handle _handler{nullptr};
};

#endif //BROKERAPP_SOCKETMANAGER_H
