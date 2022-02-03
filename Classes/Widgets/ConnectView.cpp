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

    if(ImGui::Button(_is_connected ? "Disconnect" : "Connect", ImVec2(200,50))){
        _is_connected = !_is_connected;
        client.Connect("localhost", 3200);
//        olc::net::message<CustomMsgTypes> msg;
//        client.Send()
    }

    if(ImGui::Button("Ping", ImVec2(200,50))){
        client.PingServer();
    }

    if(_is_connected) {

        if (client.IsConnected()) {
            std::cout << "Conected" << std::endl;

            if (!client.Incoming().empty()) {

                std::cout << "Not empty" << std::endl;
            }
        }
        else {
            std::cout << "Server Down\n";
        }

        ////
    } else {
//            ws.Disconnect();
    }



}

void ConnectView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
