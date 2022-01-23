//
// Created by Luiz Veloso on 21/01/22.
//

#include "PSARNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "NodeType.h"
#include "UiNodeType.h"


PSARNode::PSARNode(std::shared_ptr<Indicator> psar,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("PSAR Indicator");
    setType(UiNodeType::PSAR);
    setIndicator(psar);

    const GraphNode op(NodeType::PSAR, this);
    _id = addNode(op);
}

void PSARNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void PSARNode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto psarShared = getIndicator();
    if(!psarShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &psar = *dynamic_cast<PSAR *>(psarShared.get());

    //TODO: Create rule...
//    if (psar.size() > 0)
//        stack.push(psar[0]);
//    else
        stack.push(0.0f);

}

void PSARNode::initStyle() {
    auto psarShared = getIndicator();
    if(!psarShared) {
        INode::initStyle();
        return;
    }

    auto &psar = *dynamic_cast<PSAR*>(psarShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(psar.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(psar.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(psar.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(psar.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(psar.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void PSARNode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}