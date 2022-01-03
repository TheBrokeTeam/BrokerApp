//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "TestResultNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

TestResultNode::TestResultNode() {
    setName("Result");
    _idInput =  addInput(Type::Int);
}

void TestResultNode::onRender() {
   INode::onRender();

    //do the node's job
    _input = getValueFromId<int>(_idInput);

    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImGui::SameLine();

    const int maxSize = 20;
    char buff[maxSize] = "";
    std::string word = std::to_string(_input);
    int lastIdx = 0;
    for(int i= 0; i < word.length();i++){
        buff[i] = word[i];
        lastIdx = i;
        if(i >= maxSize-1) {
            lastIdx = maxSize-1;
            break;
        }
    }

    buff[++lastIdx] = '\0';

    ImGui::SetNextItemWidth(60);
    ImGui::InputText("##input",buff,std::min((int)word.length(),maxSize),ImGuiInputTextFlags_ReadOnly);
    ImNodes::EndInputAttribute();
}

//void TestResultNode::setInput(int id,int value) {
//    if(id == _idInput)
//        _input = value;
//}

TestResultNode::~TestResultNode() {

}

