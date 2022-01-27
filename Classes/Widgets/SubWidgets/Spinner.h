//
// Created by Maykon Meneghel on 24/01/22.
//

#ifndef BROKERAPP_SPINNER_H
#include <cmath>
#define BROKERAPP_SPINNER_H

#ifndef IMGUI_API
#include <imgui.h>
#endif //IMGUI_API

namespace ImGui {
    IMGUI_API bool Spinner(const char* label, float radius, int thickness, const ImU32& color);
    IMGUI_API void LoadingIndicatorCircle(const char* label, const float indicator_radius,
                                          const ImVec4& main_color, const ImVec4& backdrop_color,
                                          const int circle_count, const float speed);
}


#endif //BROKERAPP_SPINNER_H
