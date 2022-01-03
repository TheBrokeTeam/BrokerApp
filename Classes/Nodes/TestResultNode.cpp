//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "TestResultNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

TestResultNode::TestResultNode() {
    setName("Result");
    _idInput =  addInput();
}

void TestResultNode::onRender(float dt) {
    //do the node's job
    _input = getValueFromId(_idInput);

    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(60);
    ImGui::InputDouble("##value",&_input,0,0,"%.3f",ImGuiInputTextFlags_ReadOnly);
    ImNodes::EndInputAttribute();
}

TestResultNode::~TestResultNode() {}

