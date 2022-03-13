//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_MAINMENUBAR_H
#define BROKERAPP_MAINMENUBAR_H



//= INCLUDES =============================
#include "Widget.h"
#include <memory>
//========================================

class MainMenuBar : public Widget
{
public:
    MainMenuBar(Context* context);
    void updateVisible(float dt) override;
    void onShow() override;
    void onHide() override;
    void updateAlways(float dt) override;
    static float GetPadding() { return 8.0f; }
private:
    void showBacktestContextViews();
    void showLiveContextViews();

};

#endif //BROKERAPP_MAINMENUBAR_H
