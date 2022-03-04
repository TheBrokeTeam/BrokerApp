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
    static ImVec4 bull_color() { return {0.5,1,0,1}; };
    static ImVec4 bear_color() { return {1,0,0.5,1}; };
};




#endif //BROKERAPP_BROKERCOLORSIMGUI_H
