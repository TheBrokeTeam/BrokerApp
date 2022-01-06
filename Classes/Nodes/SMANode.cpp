//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include "../Tickables/Indicators/SMA.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


SMANode::SMANode(SMA* sma, std::shared_ptr<graph::Graph<GraphNode>> graph):_sma(std::move(sma)),_graph(graph){
    setName("SMA Indicator");
    setType(UiNodeType::SMA);
    const GraphNode op(NodeType::SMA, this);
    _id = graph->insert_node(op);
}

void SMANode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void SMANode::handleStack(std::stack<float> &stack) {
    auto& sma = *dynamic_cast<SMA*>(_sma.get());

    if(sma.size() > 0){
        stack.push(sma[0]);
        return;
    }

    stack.push(0.0f);
}

void SMANode::initStyle() {

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(_sma->getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void SMANode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}