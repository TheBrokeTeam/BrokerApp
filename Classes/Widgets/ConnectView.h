//
// Created by Maykon Meneghel on 28/01/22.
//

#ifndef BROKERAPP_CONNECTVIEW_H
#define BROKERAPP_CONNECTVIEW_H


#include "Widget.h"

#define ASIO_STANDALONE
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

class ConnectView : public Widget {
public:
    explicit ConnectView(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

private:
    void grabSomeData(asio::ip::tcp::socket&);
};

#endif //BROKERAPP_CONNECTVIEW_H
