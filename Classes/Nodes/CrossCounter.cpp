//
// Created by Arthur Abel Motelevicz on 05/01/22.
//
#include "CrossCounter.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

CrossCounter::CrossCounter(StrategyEditor* nodeEditor):INode(nodeEditor)
{
    setName("Counter");
    setType(UiNodeType::COUNTER);;
    setIcon(static_cast<int>(Editor::Icons::node_counter_black));

    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::CROSS_COUNTER, this);

    _idInput = addNode(value);
    _id = addNode(op);

    addEdge(_id, _idInput);
}


void CrossCounter::onRender(float dt) {
    bool isInputConnected = numberOfConnectionsTo(_idInput) > 0;
    ImNodes::BeginInputAttribute(_idInput, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);

    if(!isInputConnected)
        _counter = 0;

    ImGui::TextUnformatted("A");
    ImGui::SameLine();
    ImGui::Text("%d",_counter);
    ImNodes::EndInputAttribute();
}


void CrossCounter::handleStack(std::stack<float> &stack) {
    const float inputValue = stack.top();
    stack.pop();
    if (inputValue > 0) {
        _counter++;
    }
}

CrossCounter::~CrossCounter() {}

int CrossCounter::getRootNodeConnectionsNumber() {
    return numberOfConnectionsTo(_idInput);
}

