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
    MainMenuBar(Editor* editor);

    inline static bool _show_downloader = true;
    inline static bool _show_stocklist = true;
    inline static bool _show_simulator = true;
    inline static bool _show_charts = true;
    inline static bool _show_indicators = true;
    inline static bool _show_tabbars = false;
    inline static bool _showAboutWindow     = false;
    inline static bool _imgui_metrics         = false;
    inline static bool _imgui_style           = false;
    inline static bool _imgui_demo            = false;
    inline static bool _implot_demo            = false;

    void updateVisible(float dt) override;
    void onShow() override;
    void onHide() override;
    void updateAlways(float dt) override;
    static float GetPadding() { return 8.0f; }
private:
};

#endif //BROKERAPP_MAINMENUBAR_H
