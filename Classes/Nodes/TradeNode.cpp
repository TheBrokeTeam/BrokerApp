//
// Created by Arthur Abel Motelevicz on 07/01/22.
//

#include "TradeNode.h"
#include "../Editor.h"
TradeNode::TradeNode(StrategyEditor *nodeEditor,TradeNodeStrategy* strategy) : INode(nodeEditor), _strategy(strategy) {
    setNodeName("Trade");
    setType(UiNodeType::TRADE);;
    setIcon(static_cast<int>(Editor::Icons::node_trade_black));

    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::TRADE, this);

    _idInputLong = addNode(value);
    _idInputShort = addNode(value);

    _id = addNode(op);

    addEdge(_id, _idInputLong);
    addEdge(_id, _idInputShort);
}

void TradeNode::onRender(float dt) {
    const float node_width = 100.f;
    {
        bool isInputConnected = numberOfConnectionsTo(_idInputLong) > 0;
        ImNodes::BeginInputAttribute(_idInputLong, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        ImGui::TextUnformatted("long");
        ImNodes::EndInputAttribute();
    }


    {
        bool isInputConnected = numberOfConnectionsTo(_idInputShort) > 0;
        ImNodes::BeginInputAttribute(_idInputShort, isInputConnected ? ImNodesPinShape_CircleFilled : ImNodesPinShape_Circle);
        ImGui::TextUnformatted("short");
        ImNodes::EndInputAttribute();
    }

    ImGui::TextUnformatted("Take profit: ");
    ImGui::SameLine();
    ImGui::PushItemWidth(node_width/2);
    ImGui::DragFloat("%##noname", &_strategy->takeProfit, 0.5f,0.0f,100.0f,"%2.0f");
    ImGui::PopItemWidth();

    ImGui::TextUnformatted("Stop loss:   ");
    ImGui::SameLine();
    ImGui::PushItemWidth(node_width/2);
    ImGui::DragFloat("%##noname2", &_strategy->stopLoss, 0.5f,0.0f,100.0f,"%2.0f");
    ImGui::PopItemWidth();
}

void TradeNode::handleStack(std::stack<float> &stack) {
    const float  inputValueLong = stack.top();
    stack.pop();
    const float  inputValueShort = stack.top();
    stack.pop();

    if(_strategy->isPositioned) return;

    if (inputValueLong > 0) {
        _strategy->openPosition(false);
        _strategy->isPositioned = true;
    }
    else if(inputValueShort > 0){
        _strategy->openPosition(true);
        _strategy->isPositioned = true;
    }
}

int TradeNode::getRootNodeConnectionsNumber() {
    return numberOfConnectionsTo(_idInputShort) + numberOfConnectionsTo(_idInputLong);
}

TradeNode::~TradeNode() {}

