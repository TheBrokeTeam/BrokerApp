//
// Created by Maykon Meneghel on 02/02/22.
//

#ifndef BROKERAPP_WEBSOCKETMANAGER_H
#define BROKERAPP_WEBSOCKETMANAGER_H

//#define ASIO_STANDALONE
//#include <asio.hpp>
//#include <asio/ts/buffer.hpp>
//#include <asio/ts/internet.hpp>
//
#include <iostream>
#include "OLCNet.h"

//enum class CustomMsgTypes : uint32_t {
//    ServerAccept,
//    ServerDeny,
//    ServerPing,
//    MessageAll,
//    ServerMessage,
//    Hi
//};

class WebSocketManager : public olc::net::client_interface<CustomMsgTypes>{
public:

    void PingServer()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::ServerPing;

        // Caution with this...
        std::chrono::system_clock::time_point timeNow = std::chrono::system_clock::now();

        msg << timeNow;
        Send(msg);
    }

    void MessageAll()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::MessageAll;
        Send(msg);
    }

    void Hi()
    {
        olc::net::message<CustomMsgTypes> msg;
        msg.header.id = CustomMsgTypes::Hi;

        msg << "Hello World\r\n";

        Send(msg);
    }
};

#endif //BROKERAPP_WEBSOCKETMANAGER_H
