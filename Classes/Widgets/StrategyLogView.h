//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_STRATEGYLOGVIEW_H
#define BROKERAPP_STRATEGYLOGVIEW_H


#include "Widget.h"
#include <rapidjson/document.h>
#include "../Data/Bot.h"
#include <list>

class StrategyLogView: public Widget {
public:
    explicit StrategyLogView(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

private:
    std::list<std::string> _headers;
};


#endif //BROKERAPP_STRATEGYLOGVIEW_H
