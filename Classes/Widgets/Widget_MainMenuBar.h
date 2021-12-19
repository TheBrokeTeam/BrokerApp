//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_WIDGET_MAINMENUBAR_H
#define BROKERAPP_WIDGET_MAINMENUBAR_H



//= INCLUDES =============================
#include "Widget.h"
#include <memory>
//========================================

namespace Spartan { class Context; }
class Widget_Toolbar;

class Widget_MainMenuBar : public Widget
{
public:
    Widget_MainMenuBar(Editor* editor);

    void updateVisible(float dt) override;
    void onShow() override;
    void onHide() override;
    void updateAlways(float dt) override;
    static float GetPadding() { return 8.0f; }
private:
};

#endif //BROKERAPP_WIDGET_MAINMENUBAR_H
