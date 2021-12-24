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

const float k_widget_default_propery        = -1.0f;
const float k_widget_position_screen_center = -2.0f;

class Widget : public Contextualizable
{
public:
    Widget(Editor* editor);
    virtual ~Widget() = default;

    void update(float dt);

    virtual void updateAlways(float dt);      // Called always
    virtual void updateVisible(float dt);     // Called only when the widget is visible
    virtual void onShow();          // Called when the window becomes visible
    virtual void onHide();          // called when the window becomes invisible

    // Properties
    float GetHeight()           const { return _height; }
    ImGuiWindow* GetWindow()    const { return _window; }
    const auto& GetTitle()      const { return _title; }
    bool& GetVisible()                { return _is_visible; }
    void SetVisible(bool is_visible)  { _is_visible = is_visible; }

    const std::string& getId(){
        return _widgetId;
    };

protected:
    std::string _widgetId{""};
    bool _is_window                  = true;
    bool _is_visible                 = true;
    int _flags                       = ImGuiWindowFlags_NoCollapse;
    float _height                    = 0;
    float _alpha                     = -1.0f;
    ImVec2 _default_value = ImVec2(k_widget_default_propery,k_widget_default_propery);
    ImVec2 _position   =   _default_value;
    ImVec2 _size       =   _default_value;
    ImVec2 _size_min   =   _default_value;
    ImVec2 _size_max   =   _default_value;
    ImVec2 _padding    =   _default_value;
    Editor* _editor                 = nullptr;
    ImGuiWindow* _window            = nullptr;
    std::string _title              = "Title";

private:
};


#endif //BROKERAPP_WIDGET_H
