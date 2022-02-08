//
// Created by Luiz Veloso on 21/01/22.
//

#include "TRIXNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


TRIXNode::TRIXNode(std::shared_ptr<Indicator> trix,StrategyEditor* nodeEditor):IndicatorBaseNode(trix, nodeEditor){
    setType(UiNodeType::TRIX);
    setGraphNode(NodeType::TRIX);

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