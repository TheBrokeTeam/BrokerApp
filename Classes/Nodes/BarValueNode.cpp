//
// Created by Arthur Abel Motelevicz on 14/01/22.
//

#include "BarValueNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

BarValueNode::BarValueNode(StrategyEditor* nodeEditor,Ticker* ticker):INode(nodeEditor),_ticker(ticker){
    setNodeName("Bar Close");
    setType(UiNodeType::TREND);
    setIcon(static_cast<int>(Editor::Icons::node_trend_black));

    const GraphNode op(NodeType::TREND, this);
    _id = addNode(op);
}

void BarValueNode::onRender(float dt) {
    const float node_width = 100.f;
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x + 20);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void BarValueNode::handleStack(std::stack<float> &stack)
{
    auto barHistory = _ticker->getBarHistory();

    //safe check
    if(barHistory->size() == 0)
    {
        stack.push(0.0f);
        return;
    }

    stack.push((*barHistory)(0,BarDataType::CLOSE));
}

BarValueNode::~BarValueNode() {}
