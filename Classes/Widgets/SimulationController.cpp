//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#include "SimulationController.h"
#include "../Editor.h"

SimulationController::SimulationController(Context* context) : Widget(context){
    _title                  = "Simulator";
    _is_window              = true;
}

void SimulationController::updateVisible(float dt) {
    Widget::updateVisible(dt);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);


    //CONTROLLERS BELOW
    PushStyleColor(ImGuiCol_SliderGrab,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_SliderGrabActive,Editor::broker_yellow);

    static float _speedSimulation = 0.1f;
    if(ImGui::SliderFloat("##Speed",&_speedSimulation,0.00f,100.00f,"%.2f")){
        getContext()->setSimulationSpeed(_speedSimulation);

    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Speed");

    ImGui::Dummy(ImVec2(200,30));


    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Play",ImVec2(200,50))) {
        puts("Clicou no botão play!!!");
        getContext()->startSimulation(nullptr);
    }

}

int SimulationController::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void SimulationController::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
