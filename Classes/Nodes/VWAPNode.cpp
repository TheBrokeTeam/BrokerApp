//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#include "VWAPNode.h"
#include "../Tickables/Indicators/VWAP.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

VWAPNode::VWAPNode(std::shared_ptr<Indicator> vwap,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("VWAP Indicator");
    setType(UiNodeType::VWAP);
    setIndicator(vwap);

    const GraphNode op(NodeType::VWAP, this);
    _id = addNode(op);
}

void VWAPNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void VWAPNode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto vwapShared = getIndicator();
    if(!vwapShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &vwap = *dynamic_cast<VWAP *>(vwapShared.get());

    if (vwap.size() > 0)
        stack.push(vwap(0));
    else
        stack.push(0.0f);

}

void VWAPNode::initStyle() {
    //safe check
    auto vwapShared = getIndicator();
    if(!vwapShared) {
        INode::initStyle();
        return;
    }

    auto &vwap = *dynamic_cast<VWAP*>(vwapShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(vwap.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(vwap.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(vwap.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(vwap.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(vwap.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void VWAPNode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}