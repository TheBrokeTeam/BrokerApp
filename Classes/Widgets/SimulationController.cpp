//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#include "SimulationController.h"
#include "../Editor.h"

SimulationController::SimulationController(Editor * editor) : Widget(editor){
    _title                  = "Simulation";
    _is_window              = true;
}

void SimulationController::updateVisible(float dt) {
    //change background of window
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    ImGui::TextColored(Editor::broker_white,"Simulator");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_clear);

    //adding the close button
    auto info = _editor->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        _editor->showSimulationController(false);
    }

    ImGui::Separator();

    ImGui::Spacing();

    //CONTROLLERS BELOW
    PushStyleColor(ImGuiCol_SliderGrab,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_SliderGrabActive,Editor::broker_yellow);

    static float _speedSimulation = 0.1f;
    if(ImGui::SliderFloat("##Speed",&_speedSimulation,0.00f,1.00f,"%.2f")){
        _editor->getContext()->setSimulationSpeed(_speedSimulation);

    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Speed");

    ImGui::Dummy(ImVec2(200,30));


    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Play",ImVec2(200,50))) {
        puts("Clicou no botão play!!!");
        _editor->getContext()->startSimulation(nullptr);
    }

}

int SimulationController::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void SimulationController::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
