//
// Created by Arthur Abel Motelevicz on 12/01/22.
//

#include "UpSequenceNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

UpSequenceNode::UpSequenceNode(StrategyEditor* nodeEditor,Ticker* ticker):INode(nodeEditor),_ticker(ticker){
    setNodeName("Up Sequence");
    setType(UiNodeType::BAR_SEQ_UP);
    setIcon(static_cast<int>(Editor::Icons::node_bar_seq_up_black));

    const GraphNode op(NodeType::BAR_SEQ_UP, this);
    _id = addNode(op);
}

void UpSequenceNode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImGui::PushItemWidth(80);
    ImGui::InputInt("size",&_sequence);
    ImGui::PopItemWidth();

    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x + 20);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void UpSequenceNode::handleStack(std::stack<float> &stack)
{
    auto barHistory = _ticker->getBarHistory();

    //safe check
    if(barHistory->size() < _sequence)
    {
        stack.push(0.0f);
        return;
    }


    std::vector<bool> sequence;
    for(int i = 0; i < _sequence - 1; i++) {
        bool currentBarIsPositive = (*barHistory)[i].close > (*barHistory)[i].open;
        bool lastBarIsPositive = (*barHistory)[i+1].close > (*barHistory)[i+1].open;
        sequence.push_back((*barHistory)[i].close > (*barHistory)[i + 1].close && currentBarIsPositive && lastBarIsPositive);
    }

    bool isUpSequence = true;
    for(auto b : sequence)
        isUpSequence = isUpSequence && b;

    if(isUpSequence)
        stack.push(1.0);
    else
        stack.push(0.0);
}

UpSequenceNode::~UpSequenceNode() {}
