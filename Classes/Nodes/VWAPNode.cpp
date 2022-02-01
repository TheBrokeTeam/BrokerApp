//
// Created by Arthur Abel Motelevicz on 20/01/22.
//

#include "VWAPNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

VWAPNode::VWAPNode(std::shared_ptr<Indicator> vwap, StrategyEditor* nodeEditor):IndicatorBaseNode(vwap, nodeEditor){
    setType(UiNodeType::VWAP);
    setGraphNode(NodeType::VWAP);
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
