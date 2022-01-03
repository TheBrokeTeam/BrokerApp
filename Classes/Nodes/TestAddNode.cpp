//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "TestAddNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

TestAddNode::TestAddNode() {
    setName("Add");
    _idInput_a =  addInput();
    _idInput_b =  addInput();
    _idOutput = addOutput();
}

void TestAddNode::onRender(float dt) {
    //do the node's job
    _input_1 = getValueFromId(_idInput_a);
    _input_2 = getValueFromId(_idInput_b);

    _result = _input_1 + _input_2;

    setValueForId(_idOutput,_result);

    //render node
    ImNodes::BeginInputAttribute(_idInput_a);
    ImGui::Text("input 1");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputFloat("##value",&_input_1);
    ImNodes::EndInputAttribute();

    ImNodes::BeginInputAttribute(_idInput_b);
    ImGui::Text("input 2");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputFloat("##value",&_input_2);
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(ImGui::GetItemRectSize().x - 50);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    //do the node's job
    setValueForId(_idInput_a,_input_1);
    setValueForId(_idInput_b,_input_2);
}


TestAddNode::~TestAddNode() {

}



