//
// Created by Arthur Abel Motelevicz on 04/07/22.
//

#include "SourceNode.h"
#include "../Editor.h"
#include "NodeType.h"
#include "UiNodeType.h"
#include "../Widgets/StrategyEditor.h"
#include "../Tickers/Ticker.h"

SourceNode::SourceNode(StrategyEditor *strategyEditor) : INode(strategyEditor) {
    setNodeName("SourceNode");
    setIcon(static_cast<int>(Editor::Icons::node_trade));
    setType(UiNodeType::SOURCE);
    const GraphNode op(NodeType::SOURCE, this);
    _id = addNode(op);
}

void SourceNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("closed bar").x);
    auto barHistory = getNodeEditor()->getContext();
    ImGui::Text("close bar");
    ImNodes::EndOutputAttribute();
}

void SourceNode::handleStack(std::stack<float> &stack) {

//    //Safe check ---------
//    /**Todo:: call context to remove this node if the indicator is not valid anymore */
//    auto smaShared = getIndicator();
//    if(!smaShared){
//        stack.push(0.0f);
//        return;
//    }
//    //--------------------
//
//    auto &sma = *dynamic_cast<SMA *>(smaShared.get());
//
//    if (sma.size() > 0)
//        stack.push(sma(0));
//    else
//        stack.push(0.0f);

}

int SourceNode::getRootNodeConnectionsNumber() {
    return INode::getRootNodeConnectionsNumber();
}


SourceNode::~SourceNode() {}
