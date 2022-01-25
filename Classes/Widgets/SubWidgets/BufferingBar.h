//
// Created by Maykon Meneghel on 24/01/22.
//

#ifndef BROKERAPP_BUFFERINGBAR_H
#define BROKERAPP_BUFFERINGBAR_H

#ifndef IMGUI_API
#include <imgui.h>
#endif //IMGUI_API

namespace ImGui {
    IMGUI_API bool BufferingBar(const char* label, float value,  const ImVec2& size_arg, const ImU32& bg_col, const ImU32& fg_col);
}


#endif //BROKERAPP_BUFFERINGBAR_H
