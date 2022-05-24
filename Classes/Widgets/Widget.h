//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_WIDGET_H
#define BROKERAPP_WIDGET_H

//= INCLUDES =====================
#include <string>
#include <functional>
#include <imgui.h>
#include "../Contexts/Contextualizable.h"

//================================

//= FORWARD DECLARATIONS ===========================
struct ImGuiWindow;
class Editor;
//==================================================

const float k_widget_default_propery        = -1.0f; //todo: fix typo
const float k_widget_position_screen_center = -2.0f;

class Widget : public Contextualizable
{
public:
    Widget(Context* context);
    virtual ~Widget() = default;

    void update(float dt);

    virtual void updateAlways(float dt);        // Called always
    virtual void updateVisible(float dt);       // Called only when the widget is visible
    virtual void onShow();                      // Called when the window becomes visible
    virtual void onHide();                      // called when the window becomes invisible
    virtual void onPushStyleVar();              // Called just before ImGui::Begin()
    virtual void onPushStyleColor();            // Called just before ImGui::Begin()

    // Use this to push style variables. They will be automatically popped.
    template<typename T>
    void PushStyleVar(ImGuiStyleVar idx, T val) { ImGui::PushStyleVar(idx, val); _var_pushes++; }

    // Use this to push style colors. They will be automatically popped.
    template<typename T>
    void PushStyleColor(ImGuiCol_ idx, T val) { ImGui::PushStyleColor(idx, val); _color_pushes++; }

    // Properties
    float GetHeight()           const { return _height; }
    ImGuiWindow* GetWindow()    const { return _window; }
    const auto& GetTitle()      const { return _title; }
    bool& GetVisible()                { return _is_visible; }
    void SetVisible(bool is_visible)  { _is_visible = is_visible; }

    const std::string& getId(){
        return _widgetId;
    };

    void showTabBar(bool show);

    virtual int getWindowFlags();

protected:
    std::string _widgetId{""};
    bool _is_window                  = true;
    bool _is_visible                 = true;
    int _flags                       = ImGuiWindowFlags_None;
    float _height                    = 0;
    float _alpha                     = -1.0f;
    ImVec2 _default_value = ImVec2(k_widget_default_propery,k_widget_default_propery);
    ImVec2 _position   =   _default_value;
    ImVec2 _size       =   _default_value;
    ImVec2 _size_min   =   _default_value;
    ImVec2 _size_max   =   _default_value;
    ImVec2 _padding    =   _default_value;
    Context* context                = nullptr;
    ImGuiWindow* _window            = nullptr;
    std::string _title              = "Title";

private:
    uint8_t _var_pushes = 0;
    uint8_t _color_pushes = 0;
    bool _shouldShowTabbar = false;

    void popStyles();

};


#endif //BROKERAPP_WIDGET_H
