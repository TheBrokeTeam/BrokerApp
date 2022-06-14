//
// Created by Arthur Abel Motelevicz on 13/06/22.
//

#include "SliderPosition.h"
#include "../Contexts/BackTestingContext.h"

SliderPosition::SliderPosition(Context* context)
        : Widget(context){
    _title                  = "SliderPosition";
    _is_window              = false;
    _context = dynamic_cast<BackTestingContext*>(context);
}

void SliderPosition::updateAlways(float dt){

    ImGui::SetNextItemWidth(ImGui::GetWindowWidth() - (60 + 8*3 + 1));
    ImGui::PushStyleColor(ImGuiCol_SliderGrab,Editor::broker_yellow_active);
    ImGui::PushStyleColor(ImGuiCol_SliderGrabActive,Editor::broker_yellow);
    ImGui::PushStyleColor(ImGuiCol_FrameBg,Editor::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_light_grey);

    //Todo::put the slider below the chart or make other navigation
    if(ImGui::SliderFloat("##Positioner",&_currentPercent,0.000f,1.000f,"%.3f")){
        if(_changeCallback)
            _changeCallback(_currentPercent);
    }

    ImGui::PopStyleColor(5);
}

int SliderPosition::getWindowFlags(){
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void SliderPosition::onPushStyleVar(){
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);

}

void SliderPosition::setChangeCallback(ChangeCallback c){
    _changeCallback = c;
}

float SliderPosition::getPercent(){
    return _currentPercent;
}
void SliderPosition::setPercent(float p){
    _currentPercent = p;
}

