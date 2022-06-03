//
// Created by Arthur Abel Motelevicz on 25/05/22.
//

#ifndef BROKERAPP_BACKTESTTOOLBAR_H
#define BROKERAPP_BACKTESTTOOLBAR_H

#include "Widget.h"

class BackTestToolbar : public Widget {
public:
    enum class Click{
        PLAY,
        PAUSE,
        STOP
    };
    typedef std::function<void(Click)> ClickCallback;
    explicit BackTestToolbar(Context* context);
    void updateAlways(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

    void setClickCallback(ClickCallback c);

    static float GetPadding() { return 2.0f; }

private:
    bool _playing = false;
    bool _showingSpeeds = false;

    void addButton(const char* icon, float xPos, float yPos, float w, std::function<void()> callback);
    void ToolbarUI();
    ClickCallback _clickCallback{nullptr};
    void onClick(Click source);

};




#endif //BROKERAPP_BACKTESTTOOLBAR_H
