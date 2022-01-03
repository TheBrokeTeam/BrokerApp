//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "INode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

INode::INode() {
    _id =  generateId();
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 winPos = ImGui::GetCurrentWindow()->Pos;
    // TODO::understand why is that
    //this values was by try and error: ImVec2(8,35)
    pos = mousePos - winPos - ImVec2(8,35);
}


void INode::render(float dt) {

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    ImNodes::BeginNode(_id);

    if(!_init) {
        _init = true;
        ImNodes::SetNodeEditorSpacePos(_id,pos);
    }

    ImNodes::BeginNodeTitleBar();
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_black);
    ImGui::Text(_name.c_str());
    ImGui::PopStyleColor();
    ImNodes::EndNodeTitleBar();

    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
    onRender(dt);
    ImGui::PopStyleColor();


    ImNodes::EndNode();

    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}

void INode::setName(const std::string &name) {
    _name = name;
}


bool INode::hasOutput(int id) {
    for(auto outputId : _outputIds){
        if(outputId == id)
            return true;
    }
    return false;
}

bool INode::hasInput(int id) {
    for(auto inputId : _inputIds){
        if(inputId == id)
            return true;
    }
    return false;
}

int INode::addInput() {
    _inputIds.push_back(++current_id);
    _map.emplace(_inputIds.back(),0.0);
    return _inputIds.back();
}

int INode::addOutput() {
    _outputIds.push_back(++current_id);
    _map.emplace(_outputIds.back(),0.0);
    return _outputIds.back();
}


int INode::generateId() {
    return ++current_id;
}

INode::~INode() {}


