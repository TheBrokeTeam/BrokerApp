//
// Created by Arthur Abel Motelevicz on 05/01/22.
//
#include "CrossCounter.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

CrossCounter::CrossCounter(std::shared_ptr<graph::Graph<GraphNode>> graph): _graph(graph)
{
    setName("Cross counter");
    setType(UiNodeType::CROSS_COUNTER);

    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::CROSS_COUNTER, this);

    _idInput = graph->insert_node(value);
    _id = graph->insert_node(op);

    graph->insert_edge(_id, _idInput);
}


void CrossCounter::onRender(float dt) {
    const float node_width = 100.0f;
    bool isInputConnected = _graph->num_edges_from_node(_idInput) > 0;
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
    const float inputValue = stack.top();
    stack.pop();
    if(inputValue > 0)
        _counter++;
}

CrossCounter::~CrossCounter() {}

