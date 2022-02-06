//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_SOCKETSTREAMCONTROLLER_H
#define BROKERAPP_SOCKETSTREAMCONTROLLER_H

#include "Widget.h"

class SocketStreamController : public Widget
{
public:
    SocketStreamController(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

private:
    std::string _symbolName{""};
};

#endif //BROKERAPP_SOCKETSTREAMCONTROLLER_H
