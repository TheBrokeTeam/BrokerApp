//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "Widget.h"
#include <imgui_internal.h>
#include "../Editor.h"

Widget::Widget(Editor* editor)
{
    _editor    = editor;
    _context   = editor->getContext();
    _window    = nullptr;
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


void Widget::update(float dt)
{
    updateAlways(dt);

    if (!_is_window)
        return;

    bool begun = false;
    {
        if (!_is_visible)
            return;

        // Size
        if (_size.x != _default_value.x)
        {
            ImGui::SetNextWindowSize(_size, ImGuiCond_FirstUseEver);
        }

        // Max size
        if (_size_min.x != _default_value.x || _size_max.x != _default_value.x)
        {
            ImGui::SetNextWindowSizeConstraints(_size_min, _size_max);
        }

        // Padding
        if (_padding.x != _default_value.x)
        {
//            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, _padding);
//            _var_pushes++;
        }

        // Alpha
        if (_alpha != k_widget_default_propery)
        {
//            ImGui::PushStyleVar(ImGuiStyleVar_Alpha, _alpha);
//            _var_pushes++;
        }

        // Position
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
//        OnPushStyleVar();

        // Begin
        if (ImGui::Begin(_title.c_str(), &_is_visible, _flags))
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
            ImGui::End();

            // Pop style variables
//            ImGui::PopStyleVar(_var_pushes);
//            _var_pushes = 0;

        }
    }
}