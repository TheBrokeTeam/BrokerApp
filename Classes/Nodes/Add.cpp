//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

//#include "Add.h"
//#include <imgui.h>
//#include <imnodes.h>
//#include "../Editor.h"
//
//Add::Add(std::shared_ptr<graph::Graph<GraphNode>> graph):INode(graph)
//{
//    setNodeName("ADD");
//    setType(UiNodeType::ADD);
//
//    const GraphNode value(NodeType::VALUE, 0.f);
//    const GraphNode op(NodeType::ADD, this);
//
//    _idInput1 = addNode(value);
//    _idInput2 = addNode(value);
//    _plotId = addNode(op);
//
//    addEdge(_plotId, _idInput1);
//    addEdge(_plotId, _idInput2);
//}
//
//void Add::onRender(float dt) {
//    const float node_width = 100.f;
//
//    {
//        ImNodes::BeginInputAttribute(_idInput1);
//        const float label_width = ImGui::CalcTextSize("left").x;
//        ImGui::TextUnformatted("left");
//        if (numberOfConnectionsTo(_idInput1) == 0ull)
//        {
//            ImGui::SameLine();
//            ImGui::PushItemWidth(node_width - label_width);
//            ImGui::DragFloat("##hidelabel", &getGraphNode(_idInput1)->value, 0.01f);
//            ImGui::PopItemWidth();
//        }
//        ImNodes::EndInputAttribute();
//    }
//
//    {
//        ImNodes::BeginInputAttribute(_idInput2);
//        const float label_width = ImGui::CalcTextSize("right").x;
//        ImGui::TextUnformatted("right");
//        if (numberOfConnectionsTo(_idInput2) == 0ull)
//        {
//            ImGui::SameLine();
//            ImGui::PushItemWidth(node_width - label_width);
//            ImGui::DragFloat("##hidelabel", &getGraphNode(_idInput2)->value, 0.01f);
//            ImGui::PopItemWidth();
//        }
//        ImNodes::EndInputAttribute();
//    }
//
//    ImGui::Spacing();
//    {
//        ImNodes::BeginOutputAttribute(_plotId);
//        const float label_width = ImGui::CalcTextSize("result").x;
//        ImGui::Indent(node_width - label_width);
//        ImGui::TextUnformatted("result");
//        ImNodes::EndOutputAttribute();
//    }
//}
//
//void Add::handleStack(std::stack<float> &stack) {
//    const float input1Val = stack.top();
//    stack.pop();
//    const float input2Val = stack.top();
//    stack.pop();
//    stack.push(input1Val + input2Val);
//}
//
//Add::~Add() {}
