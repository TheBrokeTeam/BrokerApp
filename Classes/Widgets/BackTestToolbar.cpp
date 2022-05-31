//
// Created by Arthur Abel Motelevicz on 25/05/22.
//

#include "BackTestToolbar.h"
#include "../Editor.h"

BackTestToolbar::BackTestToolbar(Context* context) : Widget(context){
    _title                  = "BACKTEST";
    _is_window              = false;
}

void BackTestToolbar::updateAlways(float dt) {
    ToolbarUI();
}

void BackTestToolbar::ToolbarUI()
{
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, BrokerMenuBarHeight));
    ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, BrokerToolBarHeight));
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags window_flags = 0
                                    | ImGuiWindowFlags_NoDocking
                                    | ImGuiWindowFlags_NoTitleBar
                                    | ImGuiWindowFlags_NoResize
                                    | ImGuiWindowFlags_NoMove
                                    | ImGuiWindowFlags_NoScrollbar
                                    | ImGuiWindowFlags_NoSavedSettings;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(GetPadding(), GetPadding()));
    ImGui::PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);

    ImGui::Begin("TOOLBAR", NULL, window_flags);

    ImGui::TextColored(Editor::broker_white,_title.c_str());

//    ImGui::Button("Toolbar goes here", ImVec2(0, 37));

    ImGui::End();

    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(2);
}
int BackTestToolbar::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void BackTestToolbar::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void BackTestToolbar::setStopCallback(ClickCallback c){
    _stopCallback = c;
}

void BackTestToolbar::setPlayCallback(ClickCallback c){
    _playCallback = c;
}


