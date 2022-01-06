//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "SMANode.h"
#include "../Tickables/Indicators/SMA.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"


SMANode::SMANode(std::shared_ptr<Indicator> sma, std::shared_ptr<graph::Graph<GraphNode>> graph):_indicator(std::move(sma)),_graph(graph){
    setName("SMA Indicator");
    setType(UiNodeType::SMA);

//    const GraphNode value(NodeType::VALUE, 0.f);
    const GraphNode op(NodeType::SMA, this);

//    _idOutput = graph->insert_node(value);
    _id = graph->insert_node(op);

//    graph->insert_edge(_id,_idOutput);
}

void SMANode::onRender(float dt) {
    const float node_width = 100.f;
    //set node's values from indicator
    ImNodes::BeginOutputAttribute(_id);
    ImGui::Indent(node_width - ImGui::CalcTextSize("output").x);
    ImGui::Text("output");
    ImNodes::EndOutputAttribute();
}

void SMANode::handleStack(std::stack<float> &stack) {
    if(auto indicator = _indicator.lock()) {
        auto sma = dynamic_cast<SMA*>(indicator.get());

        if(sma->size() > 0){
            stack.push((*sma)[0]);
            return;
        }
    }

    stack.push(0.0f);
}

