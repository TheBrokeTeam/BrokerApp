//
// Created by Maykon Meneghel on 02/02/22.
//

#ifndef BROKERAPP_WEBSOCKETCLIENT_H
#define BROKERAPP_WEBSOCKETCLIENT_H

//#define ASIO_STANDALONE
//#include <asio.hpp>
//#include <asio/ts/buffer.hpp>
//#include <asio/ts/internet.hpp>
//
#include <iostream>
#include "WS/OLCNet.h"

//enum class CustomMsgTypes : uint32_t {
//    ServerAccept,
//    ServerDeny,
//    ServerPing,
//    MessageAll,
//    ServerMessage,
//    Hi
//};

class WebSocketClient : public olc::net::client_interface<CustomMsgTypes>{
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

        msg << "GET /chat HTTP/1.1\r\n"
            << "Host: localhost:3200\r\n"
            << "Upgrade: websocket\r\n"
            << "Connection: Upgrade\r\n"
            << "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
            << "Sec-WebSocket-Version: 13\r\n"
            << "\r\n";

        Send(msg);
    }
};

#endif //BROKERAPP_WEBSOCKETCLIENT_H
