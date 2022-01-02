//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../../Editor.h"

SMANode::SMANode() {
    setName("SMA Indicator");
    _idInput = ++current_id;
    _idOutput = ++current_id;
}

void SMANode::onRender() {
    BaseNode::onRender();

    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImNodes::EndInputAttribute();

    ImGui::SameLine();
    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(40);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}
