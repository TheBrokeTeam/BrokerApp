//
// Created by Arthur Abel Motelevicz on 05/01/22.
//
#include "CrossCounter.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

CrossCounter::CrossCounter(std::shared_ptr<graph::Graph<GraphNode>> graph):INode(graph)
{
    setName("Cross counter");
    setType(UiNodeType::CROSS_COUNTER);

    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::CROSS_COUNTER, this);

    _idInput = addNode(value);
    _id = addNode(op);

    addEdge(_id, _idInput);
}


void CrossCounter::onRender(float dt) {
    const float node_width = 100.0f;
    bool isInputConnected = numberOfConnections(_idInput) > 0;
    std::cout << "Connections: " << numberOfConnections(_idInput) << std::endl;
    ImNodes::BeginInputAttribute(_idInput, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);

    if(!isInputConnected)
        _counter = 0;

    const float label_width = ImGui::CalcTextSize("input").x;
    ImGui::TextUnformatted("input");
    ImGui::SameLine();
    ImGui::PushItemWidth(node_width - label_width);
    ImGui::Text("%d",_counter);
    ImGui::PopItemWidth();
    ImNodes::EndInputAttribute();
}


void CrossCounter::handleStack(std::stack<float> &stack) {
    std::cout << "Stack call: " << std::endl;
    const float inputValue = stack.top();
    stack.pop();
    if (inputValue > 0) {
        _counter++;
        std::cout << "Counter trigger" << std::endl;;
    }
}

CrossCounter::~CrossCounter() {}

int CrossCounter::getRootNodeConnectionsNumber() {
    return numberOfConnections(_idInput);
}

