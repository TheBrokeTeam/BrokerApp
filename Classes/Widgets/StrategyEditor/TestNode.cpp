//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "TestNode.h"
#include <imnodes.h>

TestNode::TestNode() {
    _id = ++current_id;
    _idInput = ++current_id;
    _idOutput = ++current_id;
}

void TestNode::render() {

    ImNodes::BeginNode(_id);

    ImNodes::BeginNodeTitleBar();
    ImGui::Text("simple node :)");
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

}

