//
// Created by Maykon Meneghel on 09/02/22.
//

#include "LoginView.h"
#include "../Contexts/Context.h"

LoginView::LoginView(Context *context) : Widget(context) {
    _title = "Login";
    _is_window = true;
}

void LoginView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Sign In",ImVec2(200,50)))
    {
        puts("Clicou em login!!!");
        _onLogin = true;
    }

    if(_onLogin)
    {
        ImVec2 windowSize = getContext()->getEditor()->getWindowSize();
        ImVec2 modalSize = ImVec2(200, 400);
        ImGui::SetNextWindowPos(ImVec2(windowSize.x/2 - modalSize.x/2, windowSize.y/2 - modalSize.y/2), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowSize(modalSize, ImGuiCond_FirstUseEver);
        if (ImGui::Begin("SignIn", NULL,(
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoScrollbar |
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize
                )))
        {
            if (ImGui::Button("Facebook",ImVec2(100,30)))
            {
                puts("Facebook");
            }

            if (ImGui::Button("GitHub",ImVec2(100,30)))
            {
                puts("GitHub");
            }

            if (ImGui::Button("E-mail",ImVec2(100,30)))
            {
                puts("E-mail");
            }

        }
        ImGui::End();
    }

}

int LoginView::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void LoginView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

