//
// Created by Luiz Veloso on 23/01/22.
//

#include "BaseNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


BaseNode::BaseNode(std::shared_ptr<Indicator> ind, StrategyEditor* nodeEditor): INode(nodeEditor) {

    setNodeName(ind->getName() + std::string(" Indicator"));
    setType(ind->getUiNodeType());
    setIndicator(ind);

    const GraphNode op(ind->getNodeType(), this);
    _id = addNode(op);
}

void BaseNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void BaseNode::handleStack(std::stack<float> &stack) {

    //Safe check ---------
    /**Todo:: call context to remove this node if the indicator is not valid anymore */
    auto shared = getIndicator();
    if(!shared){
        stack.push(0.0f);
        return;
    }

    // TODO: pra ficar default utilizavel precisaria herdar ReversedData direto no indicator,
    //  mas pode ter implicações maiores de arquitetura.
//    auto &ind = *shared.get();
//
//    if (ind.getSize() > 0)
//        stack.push(ind(0));
//    else
//        stack.push(0.0f);

}

void BaseNode::initStyle() {
    auto shared = getIndicator();
    if(!shared) {
        INode::initStyle();
        return;
    }

    auto &indicator = *shared.get();

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(indicator.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered,ImGui::ColorConvertFloat4ToU32(indicator.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(indicator.getColor()));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(indicator.getColor()));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(indicator.getColor()));
    ImGui::PushStyleColor(ImGuiCol_Text, Editor::broker_black);
}

void BaseNode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}