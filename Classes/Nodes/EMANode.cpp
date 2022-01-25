//
// Created by Luiz Veloso on 21/01/22.
//

#include "EMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


EMANode::EMANode(std::shared_ptr<Indicator> ema,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("EMA Indicator");
    setType(UiNodeType::EMA);
    setIndicator(ema);

    const GraphNode op(NodeType::EMA, this);
    _id = addNode(op);
}

void EMANode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void EMANode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto smaShared = getIndicator();
    if(!smaShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &ema = *dynamic_cast<EMA *>(smaShared.get());

    if (ema.size() > 0)
        stack.push(ema(0));
    else
        stack.push(0.0f);

}

void EMANode::initStyle() {
    auto smaShared = getIndicator();
    if(!smaShared) {
        INode::initStyle();
        return;
    }

    auto &ema = *dynamic_cast<EMA*>(smaShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(ema.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(ema.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(ema.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(ema.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(ema.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void EMANode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}