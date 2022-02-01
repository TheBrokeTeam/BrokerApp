//
// Created by Luiz Veloso on 21/01/22.
//

#include "PSARNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


PSARNode::PSARNode(std::shared_ptr<Indicator> psar,StrategyEditor* nodeEditor): IndicatorBaseNode(psar, nodeEditor){
    setType(UiNodeType::PSAR);
    setGraphNode(NodeType::PSAR);
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