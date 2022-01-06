////
//// Created by Arthur Abel Motelevicz on 03/01/22.
////

#include "CrossNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


CrossNode::CrossNode(std::shared_ptr<graph::Graph<GraphNode>> graph):_graph(graph) {
    setName("Cross");
    setType(UiNodeType::CROSS);

    const GraphNode value(NodeType::VALUE);
    const GraphNode op(NodeType::CROSS, this);

    _idInput1 = _graph->insert_node(value);
    _idInput2 = _graph->insert_node(value);

    _id = _graph->insert_node(op);

    _graph->insert_edge(_id,_idInput1);
    _graph->insert_edge(_id,_idInput2);
}

void CrossNode::onRender(float dt) {
    const float node_width = 100.f;

    //render node
    {
        bool isInputConnected = _graph->num_edges_from_node(_idInput1) > 0;
        ImNodes::BeginInputAttribute(_idInput1, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("input 1").x;
        ImGui::TextUnformatted("input 1");
        if (!isInputConnected) {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &_graph->node(_idInput1).value, 0.01f);
            ImGui::PopItemWidth();
        }
        else{
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::Text("%.2f", _currentInput1);
            ImGui::PopItemWidth();
        }
        ImGui::SameLine();

        ImGui::Checkbox("Cross up", &_isCrossUp);
        ImNodes::EndInputAttribute();
    }

    {
        bool isInputConnected = _graph->num_edges_from_node(_idInput2) > 0;
        ImNodes::BeginInputAttribute(_idInput2, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("input 2").x;
        ImGui::TextUnformatted("input 2");
        if (!isInputConnected) {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &_graph->node(_idInput2).value, 0.01f);
            ImGui::PopItemWidth();
        }
        else{
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::Text("%.2f", _currentInput2);
            ImGui::PopItemWidth();
        }

        ImNodes::EndInputAttribute();
    }

    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndInputAttribute();
}


void CrossNode::handleStack(std::stack<float> &stack) {
    //initial update
    _currentInput1  = stack.top();
    stack.pop();
    _currentInput2  = stack.top();
    stack.pop();

    //do the logic
    if(_isCrossUp)
        _output = _currentInput2 > _currentInput1 && _lastInput2 < _lastInput1;
    else
        _output = _currentInput2 < _currentInput1 && _lastInput2 > _lastInput1;

    //final update
    _lastInput1 = _currentInput1;
    _lastInput2 = _currentInput2;

    if(_output) {
        _countCross++;
        std::cout << "Cross: " << _countCross << std::endl;
    }


    stack.push(_output);
}

CrossNode::~CrossNode() {}

