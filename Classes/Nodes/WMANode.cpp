//
// Created by Luiz Veloso on 21/01/22.
//

#include "WMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

WMANode::WMANode(std::shared_ptr<Indicator> wma, StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("WMA Indicator");
    setType(UiNodeType::WMA);
    setIndicator(wma);

    const GraphNode op(NodeType::WMA, this);
    _id = addNode(op);
}

void WMANode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void WMANode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto wmaShared = getIndicator();
    if(!wmaShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &wma = *dynamic_cast<WMA *>(wmaShared.get());

    if (wma.size() > 0)
        stack.push(wma(0));
    else
        stack.push(0.0f);

}

void WMANode::initStyle() {
    auto wmaShared = getIndicator();
    if(!wmaShared) {
        INode::initStyle();
        return;
    }

    auto &wma = *dynamic_cast<WMA*>(wmaShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(wma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(wma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(wma.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(wma.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(wma.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void WMANode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}