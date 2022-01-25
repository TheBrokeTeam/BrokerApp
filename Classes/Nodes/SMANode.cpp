//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include "../Tickables/Indicators/SMA.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


SMANode::SMANode(std::shared_ptr<Indicator> sma,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("SMA Indicator");
    setType(UiNodeType::SMA);
    setIndicator(sma);

    const GraphNode op(NodeType::SMA, this);
    _id = addNode(op);
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

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto smaShared = getIndicator();
    if(!smaShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &sma = *dynamic_cast<SMA *>(smaShared.get());

    if (sma.size() > 0)
        stack.push(sma(0));
    else
        stack.push(0.0f);

}

void SMANode::initStyle() {
    auto smaShared = getIndicator();
    if(!smaShared) {
        INode::initStyle();
        return;
    }

    auto &sma = *dynamic_cast<SMA*>(smaShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(sma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(sma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(sma.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(sma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(sma.getColor()));
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