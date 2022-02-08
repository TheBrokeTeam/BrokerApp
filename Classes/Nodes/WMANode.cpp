//
// Created by Luiz Veloso on 21/01/22.
//

#include "WMANode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

WMANode::WMANode(std::shared_ptr<Indicator> wma, StrategyEditor* nodeEditor):IndicatorBaseNode(wma, nodeEditor){
    setType(UiNodeType::WMA);
    setGraphNode(NodeType::WMA);
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
