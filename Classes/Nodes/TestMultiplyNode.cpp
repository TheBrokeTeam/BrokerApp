//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "TestMultiplyNode.h"
#include <imgui.h>
#include <imnodes.h>

TestMultiplyNode::TestMultiplyNode() {
    setName("Multiply");
    _idInput_a =  addInput();
    _idInput_b =  addInput();
    _idOutput = addOutput();
}

void TestMultiplyNode::onRender(float dt) {
    //do the node's job
    int input1 = getValueFromId(_idInput_a);
    int input2 = getValueFromId(_idInput_b);

    _result = input1 * input2;

    setValueForId(_idOutput,_result);

    //render node
    ImNodes::BeginInputAttribute(_idInput_a);
    ImGui::Text("input 1");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##value",&input1);
    ImNodes::EndInputAttribute();

    ImNodes::BeginInputAttribute(_idInput_b);
    ImGui::Text("input 2");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100);
    ImGui::InputInt("##value",&input2);
    ImNodes::EndInputAttribute();

    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(ImGui::GetItemRectSize().x - 50);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    //do the node's job
    setValueForId(_idInput_a,input1);
    setValueForId(_idInput_b,input2);
}

TestMultiplyNode::~TestMultiplyNode() {

}
