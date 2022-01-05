//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#include "ShowOutput.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

ShowOutput::ShowOutput(std::shared_ptr<graph::Graph<GraphNode>> graph): _graph(graph)
{
    setName("Show Value");
    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::RESULT, this);

    type = UiNodeType::RESULT;
    _idInput = graph->insert_node(value);
    _id = graph->insert_node(op);

    graph->insert_edge(_id, _idInput);
}


void ShowOutput::onRender(float dt) {
    const float node_width = 100.0f;
    ImNodes::BeginInputAttribute(_idInput);
    const float label_width = ImGui::CalcTextSize("r").x;
    ImGui::TextUnformatted("r");
    if (_graph->num_edges_from_node(_idInput) == 0ull)
    {
        ImGui::SameLine();
        ImGui::PushItemWidth(node_width - label_width);
        ImGui::DragFloat("##hidelabel", &_graph->node(_idInput).value, 0.01f, 0.f, 1.0f);
        ImGui::PopItemWidth();
    }
    ImNodes::EndInputAttribute();
}

ShowOutput::~ShowOutput() {}

int ShowOutput::getIdInput() {
    return _idInput;
}

void ShowOutput::handleStack(std::stack<float> &stack) {
    _value = stack.top();
    stack.pop();
    std::cout << "ShowOutput Graph: " << _value << std::endl;
}
