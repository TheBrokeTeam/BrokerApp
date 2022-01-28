//
// Created by Maykon Meneghel on 28/01/22.
//

#include "ConnectView.h"
#include "../Editor.h"

ConnectView::ConnectView(Context *context) : Widget(context) {
    _title                  = "Connect View";
    _is_window              = true;
}

void ConnectView::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //change color text
//    PushStyleColor(ImGuiCol_Text, Editor::broker_black);

    //change background of frames
//    PushStyleColor(ImGuiCol_FrameBg, Editor::broker_white);
//    PushStyleColor(ImGuiCol_FrameBgActive, Editor::broker_white);
//    PushStyleColor(ImGuiCol_FrameBgHovered, Editor::broker_white);
//
//    //change background of items on combos
//    PushStyleColor(ImGuiCol_PopupBg, Editor::broker_white);
//
//    //change background from other buttons
//    PushStyleColor(ImGuiCol_Button, Editor::broker_white);
//    PushStyleColor(ImGuiCol_ButtonActive, Editor::broker_white);
//    PushStyleColor(ImGuiCol_ButtonHovered, Editor::broker_white);

//    ImGui::PopStyleColor(3);
}

void ConnectView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}