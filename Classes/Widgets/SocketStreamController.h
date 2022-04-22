//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_SOCKETSTREAMCONTROLLER_H
#define BROKERAPP_SOCKETSTREAMCONTROLLER_H

#include "Widget.h"
#include "../Data/Symbol.h"

class SocketStreamController : public Widget
{
public:
    SocketStreamController(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
    void testFunction();

private:
    void changeStream();
    Symbol _symbol{"ETHUSDT","1m",0,0};

    std::string _symbolName{"ETHUSDT"};
    std::string _oldSymbolName{""};

};

#endif //BROKERAPP_SOCKETSTREAMCONTROLLER_H
