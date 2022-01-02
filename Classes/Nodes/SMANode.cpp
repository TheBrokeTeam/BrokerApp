//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

SMANode::SMANode() {
    setName("SMA Indicator");
    _idInput = addInput();
    _idOutput = addOutput();
}

void SMANode::onRender() {
    BaseNode::onRender();

    ImNodes::BeginInputAttribute(_idInput,ImNodesPinShape_Circle);
    ImGui::SliderInt("Average size", &_averageSize, 1, 200);
    ImNodes::EndInputAttribute();

    ImGui::SameLine();
    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(40);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}
