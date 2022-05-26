//
// Created by Arthur Abel Motelevicz on 25/05/22.
//

#ifndef BROKERAPP_BACKTESTTOOLBAR_H
#define BROKERAPP_BACKTESTTOOLBAR_H

#include "Widget.h"

class BackTestToolbar :public Widget {
public:
    explicit BackTestToolbar(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
};




#endif //BROKERAPP_BACKTESTTOOLBAR_H
