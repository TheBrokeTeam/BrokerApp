//
// Created by Arthur Abel Motelevicz on 25/05/22.
//

#ifndef BROKERAPP_BACKTESTTOOLBAR_H
#define BROKERAPP_BACKTESTTOOLBAR_H

#include "Widget.h"

class BackTestToolbar : public Widget {
public:
    typedef std::function<void(void)> ClickCallback;
    explicit BackTestToolbar(Context* context);
    void updateAlways(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

    void setStopCallback(ClickCallback c);
    void setPlayCallback(ClickCallback c);

    static float GetPadding() { return 8.0f; }

private:
    void ToolbarUI();
    ClickCallback _stopCallback{nullptr};
    ClickCallback _playCallback{nullptr};

};




#endif //BROKERAPP_BACKTESTTOOLBAR_H
