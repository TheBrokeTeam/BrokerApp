//
// Created by Luiz Veloso on 04/03/22.
//

#ifndef BROKERAPP_BROKERCOLORSIMGUI_H
#define BROKERAPP_BROKERCOLORSIMGUI_H

#include "imgui.h"
//ref: https://stackoverflow.com/a/44124228/6704959

class BrokerColorsImgui {
public:
    BrokerColorsImgui();
    inline static const ImVec4 volume_color = ImVec4(1, 0.75,0.25,1);
    inline static const ImVec4 bull_color = ImVec4(0.5,1,0,1);
    inline static const ImVec4 bear_color = ImVec4(1,0,0.5,1);
    inline static const ImVec4 broker_yellow = ImVec4(255.0f / 255, 191.0f / 255, 64.0f / 255, 1.00f);
    inline static const ImVec4 broker_yellow_active = ImVec4(153.0f / 255, 102.0f / 255, 0.0f / 255, 1.00f);
    inline static const ImVec4 broker_yellow_hover = ImVec4(255.0f / 255, 238.0f / 255, 204.0f / 255, 1.00f);
    inline static const ImVec4 broker_white = ImVec4(220.0f / 255, 220.0f / 255, 220.0f / 255, 1.00f);
    inline static const ImVec4 broker_green = ImVec4(0.52f, 0.6f, 0.0f, 1.00f);
    inline static const ImVec4 broker_red = ImVec4(1.0f, 0.5f, 0.35f, 1.00f);
    inline static const ImVec4 broker_dark_grey = ImVec4(24.0f / 255, 26.0f / 255, 31.0f / 255, 1.00f);
    inline static const ImVec4 broker_light_grey = ImVec4(62.0f / 255, 62.0f / 255, 62.0f / 255, 1.00f);
    inline static const ImVec4 broker_clear = ImVec4(0, 0, 0, 0.00f);
    inline static const ImVec4 broker_pnl_profit = ImVec4(0.3f, 0.3f, 1.0f, 0.3f);
    inline static const ImVec4 broker_pnl_loss = ImVec4(1.0f, 0.3f, 0.3f, 0.3f);
    inline static const ImVec4 broker_pnl_profit_line = ImVec4(0.3f, 0.3f, 1.0f, 1.0f);
    inline static const ImVec4 broker_pnl_loss_line = ImVec4(1.0f, 0.3f, 0.3f, 1.0f);
    inline static const ImVec4 broker_black = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
};




#endif //BROKERAPP_BROKERCOLORSIMGUI_H
