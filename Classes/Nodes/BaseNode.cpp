//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "BaseNode.h"
#include <imgui.h>
#include <imnodes.h>

#include "../Editor.h"

BaseNode::BaseNode() {
    _id =  generateId();
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 winPos = ImGui::GetCurrentWindow()->Pos;
    // TODO::understand why is that
    //it was attempting: ImVec2(8,35)
    pos = mousePos - winPos - ImVec2(8,35);
}

void BaseNode::render() {

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
    onRender();
    ImGui::PopStyleColor();


    ImNodes::EndNode();

    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}

void BaseNode::setName(const std::string &name) {
    _name = name;
}

BaseNode::~BaseNode() {

}

void BaseNode::onRender() {

}

bool BaseNode::hasOutput(int id) {
    for(auto outputId : _outputIds){
        if(outputId == id)
            return true;
    }
    return false;
}

bool BaseNode::hasInput(int id) {
    for(auto inputId : _inputIds){
        if(inputId == id)
            return true;
    }
    return false;
}

int BaseNode::addInput() {
    _inputIds.push_back(++current_id);
    return _inputIds.back();
}

int BaseNode::addOutput() {
    _outputIds.push_back(++current_id);
    return _outputIds.back();
}

int BaseNode::generateId() {
    return ++current_id;
}

int BaseNode::getOutput(int id) {
    return 0;
}

int BaseNode::getInput(int id) {
    return 0;
}

void BaseNode::setInput(int id, int value) {

}
