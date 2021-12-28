//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Widget.h"
#include <imgui_internal.h>
#include "../Editor.h"


Widget::Widget(Editor* editor)
{
    setContext(editor->getContext());
    _editor    = editor;
    _window    = nullptr;
    _widgetId = uuid::generate_uuid_v4();
}

void Widget::updateAlways(float dt)
{

}

void Widget::updateVisible(float dt)
{

}

void Widget::onShow()
{

}

void Widget::onHide()
{

}

void Widget::onPushStyleVar() {

}

void Widget::onPushStyleColor() {

}



void Widget::update(float dt)
{
    updateAlways(dt);

    if (!_is_window){
        popStyles();
        return;
    }

    bool begun = false;

    {
        if (!_is_visible)
            return;

        // Size
//        if (_size.x != _default_value.x)
//        {
//            ImGui::SetNextWindowSize(_size, ImGuiCond_FirstUseEver);
//        }

        // Max size
//        if (_size_min.x != _default_value.x || _size_max.x != _default_value.x)
//        {
//            ImGui::SetNextWindowSizeConstraints(_size_min, _size_max);
//        }

        // Padding
//        if (_padding.x != _default_value.x)
//        {
//            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, _padding);
//            _var_pushes++;
//        }

        // Alpha
//        if (_alpha != k_widget_default_propery)
//        {
//            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, _alpha);
//            _var_pushes++;
//        }

//         Position
        if (_position.x != _default_value.x)
        {
            if (_position.x == k_widget_position_screen_center)
            {
                _position.x = _editor->getWindowSize().x * 0.5f;
                _position.y = _editor->getWindowSize().y * 0.5f;
            }

            ImVec2 pivot_center = ImVec2(0.5f, 0.5f);
            ImGui::SetNextWindowPos(_position, ImGuiCond_FirstUseEver, pivot_center);
        }

        // Callback
        onPushStyleVar();
        onPushStyleColor();

        //Tabbar handle-----------------
        ImGuiWindowClass window_class;
        if(!_shouldShowTabbar)
            window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_NoTabBar;
        else
            window_class.DockNodeFlagsOverrideSet = ImGuiDockNodeFlags_None;
        ImGui::SetNextWindowClass(&window_class);
        //---------------------------------------


        // Begin
        if (ImGui::Begin(_title.c_str(), nullptr, getWindowFlags()))
        {
            _window = ImGui::GetCurrentWindow();
            _height = ImGui::GetWindowHeight();
            begun = true;
        }
        else if (_window && _window->Hidden)
        {
            // Enters here if the window is hidden as part of an unselected tab.
            // ImGui::Begin() makes the window but returns false, then ImGui still expects ImGui::End() to be called.
            // So we make sure that when Widget::End() is called, ImGui::End() get's called as well.
            // Note: ImGui's docking is in beta, so maybe it's at fault here ?
            begun = true;
        }

        // Callbacks
        if (_window && _window->Appearing)
        {
            onShow();
        }
        else if (!_is_visible)
        {
            onHide();
        }
    }

    if (begun)
    {
        updateVisible(dt);
        {
            // End
            popStyles();
            ImGui::End();

        }
    }
}

void Widget::popStyles() {
    //Pop style variables
    ImGui::PopStyleVar(_var_pushes);
    _var_pushes = 0;
    //Pop color variables
    ImGui::PopStyleColor(_color_pushes);
    _color_pushes = 0;
}

int Widget::getWindowFlags() {
    return _flags;
}

void Widget::showTabBar(bool show) {
    _shouldShowTabbar = show;
}

