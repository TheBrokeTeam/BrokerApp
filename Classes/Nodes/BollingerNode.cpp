//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#include "BollingerNode.h"
#include "../Tickables/Indicators/Bollinger.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


BollingerNode::BollingerNode(std::shared_ptr<Indicator> bollinger,StrategyEditor* nodeEditor):INode(nodeEditor){
    setNodeName("BOLL Indicator");
    setType(UiNodeType::BOLL);
    setIndicator(bollinger);

    const GraphNode op(NodeType::BOLL, this);
    _id = addNode(op);
}

void BollingerNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    static int e = 0;

    ImGui::RadioButton("top",&_radioBtn,1);
    ImGui::RadioButton("bottom",&_radioBtn,2);

    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void BollingerNode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto smaShared = getIndicator();
    if(!smaShared){
        stack.push(0.0f);
        return;
    }
    //--------------------

    auto &boll = *dynamic_cast<Bollinger *>(smaShared.get());

    if (boll.size() > 0 && _radioBtn == 1)
        stack.push(boll[0].top);
    else if (boll.size() > 0 && _radioBtn == 2)
        stack.push(boll[0].bottom);
    else
        stack.push(0.0f);

}

void BollingerNode::initStyle() {
    auto smaShared = getIndicator();
    if(!smaShared) {
        INode::initStyle();
        return;
    }

    auto &boll = *dynamic_cast<Bollinger*>(smaShared.get());

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(boll.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(boll.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(boll.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(boll.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(boll.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void BollingerNode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}