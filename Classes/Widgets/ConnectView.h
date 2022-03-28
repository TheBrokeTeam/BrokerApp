//
// Created by Maykon Meneghel on 28/01/22.
//

#ifndef BROKERAPP_CONNECTVIEW_H
#define BROKERAPP_CONNECTVIEW_H


#include "Widget.h"
#include "../Networking/WebSocket/WebSocketManager.h"
#include "../Networking/WebSocket/WSMessage.h"

class ConnectView : public Widget {
public:
    explicit ConnectView(Context *context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
private:
    WebSocketManager client;
    void GrabSomeData(asio::ip::tcp::socket& socket);
    bool _is_connected = false;
};

#endif //BROKERAPP_CONNECTVIEW_H
