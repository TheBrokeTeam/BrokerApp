////
//// Created by Arthur Abel Motelevicz on 03/01/22.
////

#include "CrossNode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "NodeType.h"
#include "UiNodeType.h"

CrossNode::CrossNode(StrategyEditor* nodeEditor):INode(nodeEditor) {
    setNodeName("Cross");
    setType(UiNodeType::CROSS);
    setIcon(static_cast<int>(Editor::Icons::node_cross_black));

    const GraphNode value(NodeType::VALUE);
    const GraphNode op(NodeType::CROSS, this);

    _idInput1 = addNode(value);
    _idInput2 = addNode(value);
    _id = addNode(op);

    addEdge(_id,_idInput1);
    addEdge(_id,_idInput2);
}

void CrossNode::onRender(float dt) {
    const float node_width = 50.f;

    {
        bool isInputConnected = numberOfConnectionsTo(_idInput1) > 0;
        ImNodes::BeginInputAttribute(_idInput1, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("A").x;
        ImGui::TextUnformatted("A");
        ImGui::SameLine();
        const float label_up_width = ImGui::CalcTextSize("up").x;
        ImGui::Indent(node_width - label_up_width);
        ImGui::Checkbox("up", &_isCrossUp);
        ImNodes::EndInputAttribute();
    }

    {
        bool isInputConnected = numberOfConnectionsTo(_idInput2) > 0;
        ImNodes::BeginInputAttribute(_idInput2, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        ImGui::TextUnformatted("B");
        ImNodes::EndInputAttribute();
    }
    {
        ImGui::SameLine();
        bool isOutputConnected = numberOfConnectionsFrom(_id) > 0;
        ImNodes::BeginOutputAttribute(_id,isOutputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        const float label_width = ImGui::CalcTextSize("out").x;
        ImGui::Indent(node_width - label_width + 6);
        ImGui::Text("out");
        ImNodes::EndInputAttribute();
    }
}


void CrossNode::handleStack(std::stack<float> &stack) {
    //initial update
    //the order get from stack is inverse the added on graph **????
    _currentInput2  = stack.top();
    stack.pop();
    _currentInput1  = stack.top();
    stack.pop();

    //do the logic
    if(!_isCrossUp)
        _output = _currentInput2 > _currentInput1 && _lastInput2 < _lastInput1;
    else
        _output = _currentInput2 < _currentInput1 && _lastInput2 > _lastInput1;

    stack.push(_output);
}

//delete graph relations
CrossNode::~CrossNode() {}

void CrossNode::endEvaluate()
{
    _lastInput1 = _currentInput1;
    _lastInput2 = _currentInput2;
}



