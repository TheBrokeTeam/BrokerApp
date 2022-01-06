////
//// Created by Arthur Abel Motelevicz on 03/01/22.
////

#include "CrossNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


CrossNode::CrossNode(std::shared_ptr<graph::Graph<GraphNode>> graph):INode(graph) {
    setName("Cross");
    setType(UiNodeType::CROSS);

    const GraphNode value(NodeType::VALUE);
    const GraphNode op(NodeType::CROSS, this);

    _idInput1 = addNode(value);
    _idInput2 = addNode(value);
    _id = addNode(op);

    addEdge(_id,_idInput1);
    addEdge(_id,_idInput2);
}

void CrossNode::onRender(float dt) {
    const float node_width = 120.f;

    //render node
    {
        bool isInputConnected = numberOfConnections(_idInput1) > 0;
        ImNodes::BeginInputAttribute(_idInput1, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("input 1").x;
        ImGui::TextUnformatted("input 1");
        if (!isInputConnected) {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &getGraphNode(_idInput1)->value, 0.01f);
            ImGui::PopItemWidth();
        }
//        else{
//            ImGui::SameLine();
//            ImGui::PushItemWidth(node_width - label_width);
//            ImGui::Text("%.2f", _currentInput1);
//            ImGui::PopItemWidth();
//        }
        ImGui::SameLine();

        ImGui::Checkbox("Cross up", &_isCrossUp);
        ImNodes::EndInputAttribute();
    }

    {
        bool isInputConnected = numberOfConnections(_idInput2) > 0;
        ImNodes::BeginInputAttribute(_idInput2, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("input 2").x;
        ImGui::TextUnformatted("input 2");
        if (!isInputConnected) {
            ImGui::SameLine();
            ImGui::PushItemWidth(node_width - label_width);
            ImGui::DragFloat("##hidelabel", &getGraphNode(_idInput2)->value, 0.01f);
            ImGui::PopItemWidth();
        }
//        else{
//            ImGui::SameLine();
//            ImGui::PushItemWidth(node_width - label_width);
//            ImGui::Text("%.2f", _currentInput2);
//            ImGui::PopItemWidth();
//        }

        ImNodes::EndInputAttribute();
    }

    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(ImGui::GetItemRectSize().x + ImGui::CalcTextSize("output").x);
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

    if(_output)
        _countCross++;

    stack.push(_output);
}

//delete graph relations
CrossNode::~CrossNode() {}

