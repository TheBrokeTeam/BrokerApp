//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#include "Add.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"

Add::Add(std::shared_ptr<graph::Graph<GraphNode>> graph): _graph(graph)
{
    setName("ADD");
    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::ADD);

    type = UiNodeType::ADD;
    idInput1 = graph->insert_node(value);
    idInput2 = graph->insert_node(value);
    id = graph->insert_node(op);

    graph->insert_edge(id, idInput1);
    graph->insert_edge(id, idInput2);
}

Add::~Add() {}

void Add::onRender(float dt) {
    const float node_width = 100.f;

    {
        ImNodes::BeginInputAttribute(idInput1);
        const float label_width = ImGui::CalcTextSize("left").x;
        ImGui::TextUnformatted("left");
        if (_graph->num_edges_from_node(idInput1) == 0ull)
        {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &_graph->node(idInput1).value, 0.01f);
            ImGui::PopItemWidth();
        }
        ImNodes::EndInputAttribute();
    }

    {
        ImNodes::BeginInputAttribute(idInput2);
        const float label_width = ImGui::CalcTextSize("right").x;
        ImGui::TextUnformatted("right");
        if (_graph->num_edges_from_node(idInput2) == 0ull)
        {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &_graph->node(idInput2).value, 0.01f);
            ImGui::PopItemWidth();
        }
        ImNodes::EndInputAttribute();
    }

    ImGui::Spacing();
    {
        ImNodes::BeginOutputAttribute(id);
        const float label_width = ImGui::CalcTextSize("result").x;
        ImGui::Indent(node_width - label_width);
        ImGui::TextUnformatted("result");
        ImNodes::EndOutputAttribute();
    }
}
