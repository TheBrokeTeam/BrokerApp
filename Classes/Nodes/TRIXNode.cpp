//
// Created by Luiz Veloso on 21/01/22.
//

#include "TRIXNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "NodeType.h"
#include "UiNodeType.h"


TRIXNode::TRIXNode(std::shared_ptr<Indicator> trix,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("TRIX Indicator");
    setType(UiNodeType::TRIX);
    setIndicator(trix);

    const GraphNode op(NodeType::TRIX, this);
    _id = addNode(op);
}

void TRIXNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void TRIXNode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto trixShared = getIndicator();
    if(!trixShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &trix = *dynamic_cast<TRIX *>(trixShared.get());

    if (trix.size() > 0)
        stack.push(trix(0));
    else
        stack.push(0.0f);

}

void TRIXNode::initStyle() {
    auto trixShared = getIndicator();
    if(!trixShared) {
        INode::initStyle();
        return;
    }
    auto &trix = *dynamic_cast<TRIX *>(trixShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(trix.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(trix.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(trix.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(trix.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(trix.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void TRIXNode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}