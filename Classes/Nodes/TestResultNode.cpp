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

    if(_input > 0)
        std::cout << "Cross count: " << ++_count<< std::endl;

    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##value",&_count);
    ImNodes::EndInputAttribute();
}

TestResultNode::~TestResultNode() {}

