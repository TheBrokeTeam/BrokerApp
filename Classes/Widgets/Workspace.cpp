//
// Created by Arthur Abel Motelevicz on 26/12/21.
//

#include "Workspace.h"
#include <imgui_internal.h>

Workspace::Workspace(Editor *editor) : Widget(editor) {
    _is_visible = true;
    _is_window = true;
}

void Workspace::updateVisible(float dt) {
//    ImGui::BeginChild("##workspace");
//
//    ImGui::EndChild();
}

void Workspace::onPushStyleVar() {
    PushStyleVar(ImGuiStyleVar_WindowMinSize,ImVec2(ImGui::GetWindowWidth(),ImGui::GetWindowHeight()));
    PushStyleVar(ImGuiStyleVar_WindowPadding,ImVec2(0,0));
    PushStyleVar(ImGuiStyleVar_FramePadding,ImVec2(0,0));

    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_yellow);
}

void Workspace::onPushStyleColor() {

}

int Workspace::getWindowFlags() {
    return  ImGuiWindowFlags_NoDocking             |
            ImGuiWindowFlags_NoTitleBar            |
            ImGuiWindowFlags_NoCollapse            |
            ImGuiWindowFlags_NoResize              |
            ImGuiWindowFlags_NoMove                |
            ImGuiWindowFlags_NoBringToFrontOnFocus |
            ImGuiWindowFlags_NoNavFocus;
}
