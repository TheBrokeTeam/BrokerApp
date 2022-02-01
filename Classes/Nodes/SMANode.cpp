//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


SMANode::SMANode(std::shared_ptr<Indicator> sma, StrategyEditor* nodeEditor): IndicatorBaseNode(sma, nodeEditor) {
    setType(UiNodeType::SMA);
    setGraphNode(NodeType::SMA);
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