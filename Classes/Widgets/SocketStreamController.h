//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_SOCKETSTREAMCONTROLLER_H
#define BROKERAPP_SOCKETSTREAMCONTROLLER_H

#include "Widget.h"
#include "../Data/Symbol.h"
#include "../Tickables/Strategies/ManualStrategy.h"

class SocketStreamController : public Widget
{
public:
    SocketStreamController(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
    void testFunction();
    void setStrategyTest(std::weak_ptr<Strategy> strategy);

private:
    void changeStream();
    Symbol _symbol{"ETHUSDT","1m",0,0};

    std::string _symbolName{"ETHUSDT"};
    std::string _oldSymbolName{""};

    std::weak_ptr<Strategy> _strategy;
};

#endif //BROKERAPP_SOCKETSTREAMCONTROLLER_H
