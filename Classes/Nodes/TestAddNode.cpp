//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "TestAddNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

TestAddNode::TestAddNode() {
    setName("Add");
    _idInput_a =  addInput(Type::Float);
    _idInput_b =  addInput(Type::Float);
    _idOutput = addOutput(Type::Float);
}

void TestAddNode::onRender() {
    INode::onRender();

    //do the node's job
    _input_1 = 10;//getValueFromId<int>(_idInput_a);
    _input_2 = 15;// getValueFromId<int>(_idInput_b);

    _result = _input_1 + _input_2;

    setValueForId<int>(_idOutput,_result);

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
}

int TestAddNode::getResult() const{
    return _result;
}

//void TestAddNode::setInput(int id, int value) {
//    if(id == _idInput_a){
//        _input_1 = value;
//        return;
//    }
//
//    if(id == _idInput_b){
//        _input_2 = value;
//        return;
//    }
//}

//int TestAddNode::getOutput(int id) {
//    if(id == _idOutput){
//        return _result;
//    }
//    return 0;
//}

//int TestAddNode::getInput(int id)
//{
//    if(id == _idInput_a){
//        return _input_1;
//    }
//
//    if(id == _idInput_b){
//        return _input_2;
//    }
//}

TestAddNode::~TestAddNode() {

}



