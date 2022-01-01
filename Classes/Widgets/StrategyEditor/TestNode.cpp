//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "TestNode.h"
#include <imgui.h>
#include <imnodes.h>

#include "../../Editor.h"

TestNode::TestNode() {
    _id = ++current_id;
    _idInput = ++current_id;
    _idOutput = ++current_id;
}

void TestNode::render() {

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::BeginNode(_id);

    ImNodes::BeginNodeTitleBar();
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_black);
    ImGui::Text("simple node :)");
    ImGui::PopStyleColor();
    ImNodes::EndNodeTitleBar();


    ImNodes::BeginInputAttribute(_idInput);
    ImGui::Text("input");
    ImNodes::EndInputAttribute();

    ImGui::SameLine();
    ImNodes::BeginOutputAttribute(_idOutput);

    ImGui::Indent(40);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();

    ImNodes::EndNode();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();


}

