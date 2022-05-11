//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "INode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "../Widgets/StrategyEditor.h"
#include "UiNodeType.h"
#include <utility>


INode::INode(StrategyEditor* strategyEditor): _nodeEditor(strategyEditor)
{
    _graph = strategyEditor->getGraph();
}

INode::INode(const NodeInfo& info) {
    this->_id = info.id;
    this->_name = info.name;
    this->_pos = info.position;
    this->_type = info.nodeType;
    this->_icon = info.icon;
    this->_internalNodes = info.internalNodes;
    this->_isIndicatorNode = info.isIndicatorNode;
    this->_init = info._init;

    _graph = this->_nodeEditor->getGraph();
}

void INode::render(float dt) {
    initStyle();
    ImNodes::BeginNode(_id);

    if(!_init) {
        _init = true;
        ImNodes::SetNodeEditorSpacePos(_id,_pos);
    }

    ImNodes::BeginNodeTitleBar();
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_dark_grey);
    ImGui::Text(_name.c_str());
    //has icon to render
    if(_icon != 0){
        ImGui::SameLine();
        auto info = _nodeEditor->getContext()->getEditor()->getTexture(Editor::Icons(_icon));
//        ImGui::SetCursorPosX(nodeWidth / 2 - info.my_image_width/2 - 4);
        const float titleSize = ImGui::CalcTextSize(_name.c_str()).x;
//        ImGui::Indent(titleSize);
        ImGui::Image((void *) (intptr_t) info.my_image_texture,
                           ImVec2(info.my_image_width, info.my_image_height));
    }

    ImGui::PopStyleColor();
    ImNodes::EndNodeTitleBar();

    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_white);
    onRender(dt);
    ImGui::PopStyleColor();

    ImNodes::EndNode();

    finishStyle();
}

void INode::setNodeName(const std::string &name) {
    _name = name;
}

const UiNodeType &INode::getType() {
    return _type;
}

void INode::setType(const UiNodeType &type) {
    _type = type;
}

void INode::setIcon(int icon) {
    _icon = icon ;
}

void INode::initStyle() {

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImGui::PushStyleColor(ImGuiCol_Text,Editor::broker_black);

}

void INode::finishStyle() {
    ImGui::PopStyleColor();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
}

int INode::addNode(const GraphNode& node) {
    int id = _graph->insert_node(node);
    _internalNodes.push_back(id);
    return id;
}

int INode::addEdge(int from, int to) {
    return _graph->insert_edge(from,to);
}

int INode::numberOfConnectionsTo(int nodeId) {
    return _graph->num_edges_from_node(nodeId);
}

int INode::numberOfConnectionsFrom(int nodeId) {
    int countToNode = 0;
    auto edges = _graph->edges();
    for(auto& e : edges){
        if(e.to == nodeId)
            countToNode++;
    }
    return countToNode;
}

GraphNode *INode::getGraphNode(int id) {
    return &_graph->node(id);
}

INode::~INode() {
    for(auto id : _internalNodes)
        _graph->erase_node(id);

    _internalNodes.clear();
}

rapidjson::Document INode::toJson() {

    auto jsonDoc = BAJson::document();

    BAJson::set(jsonDoc, "id", this->_id);
    BAJson::set(jsonDoc, "name", this->_name);
    BAJson::set(jsonDoc, "nodeType", INode::typeToString(this->_type));

    std::vector<float> pos = { this->_pos.x, this->_pos.y };
    BAJson::set(jsonDoc, "position", pos);

    BAJson::set(jsonDoc, "_init", this->_init);
    BAJson::set(jsonDoc, "icon", this->_icon);
    BAJson::set(jsonDoc, "isIndicatorNode", this->_isIndicatorNode);

    BAJson::set(jsonDoc, "internalNodes", this->_internalNodes);

    rapidjson::Document jsonInternalEdges;
    jsonInternalEdges.SetArray();

    bool isEmpty = true;

    for(auto internalNode : this->_internalNodes)
    {
        rapidjson::Document jsonInternalEdge = BAJson::document();

        rapidjson::Document jsonNeighbors;
        jsonNeighbors.SetArray();
        for(auto neighborNode: _graph->neighbors(internalNode))
        {
            rapidjson::Document jsonN = BAJson::document();
            BAJson::set(jsonN, "from", std::to_string(internalNode));
            BAJson::set(jsonN, "to", std::to_string(neighborNode));
            BAJson::append(jsonNeighbors, jsonN);
            isEmpty = false;
        }

        BAJson::set(jsonInternalEdge, std::to_string(internalNode), jsonNeighbors);
        BAJson::append(jsonInternalEdges, jsonInternalEdge);
    }

    if(!isEmpty) {
        BAJson::set(jsonDoc, "internalEdges", jsonInternalEdges);
    }

    return jsonDoc;
}

//rapidjson::Document NodeInfo::getEdgeFromInternalNode(graph::Graph<GraphNode> *graph, int nodeId)
//{
//    rapidjson::Document doc = BAJson::document();
//
//    rapidjson::Document doc2 = BAJson::document();
//    doc2.SetArray();
//
//    for(auto& from : graph->neighbors(nodeId))
//    {
//        rapidjson::Document edgeDoc = BAJson::document();
//        BAJson::set(edgeDoc, "from", from);
//        BAJson::set(edgeDoc, "to", nodeId);
//        BAJson::append(doc2, edgeDoc);
//    }
//
//    rapidjson::Value v(doc2, doc.GetAllocator());
//
//    BAJson::set(doc, std::to_string(nodeId),v);
//
//    return doc;
//}

NodeInfo INode::toInfo() {
    return {
            this->_id,
            this->_type,
            this->_pos,
            this->_name,
            this->_internalNodes,
            this->_internalEdges,
            this->_init,
            this->_isIndicatorNode,
            this->_icon
    };
}

std::string INode::typeToString(const UiNodeType& type) {
    switch (type) {
        case UiNodeType::EMA:               return "EMA";
        case UiNodeType::BAR_SEQ_DOWN:      return "BAR_SEQ_DOWN";
        case UiNodeType::BAR_SEQ_UP:        return "BAR_SEQ_UP";
        case UiNodeType::BOLL:              return "BOLL";
        case UiNodeType::COUNTER:           return "COUNTER";
        case UiNodeType::CROSS:             return "CROSS";
        case UiNodeType::PSAR:              return "PSAR";
        case UiNodeType::TRADE:             return "TRADE";
        case UiNodeType::TREND:             return "TREND";
        case UiNodeType::TRIX:              return "TRIX";
        case UiNodeType::VWAP:              return "VWAP";
        case UiNodeType::WMA:               return "WMA";
        case UiNodeType::SMA:               return "SMA";
        default:                            return "[Unknown Node Type]";
    }
}

UiNodeType INode::stringToUiNodeType(const std::string& str) {
    if ( str == "EMA" )    return UiNodeType::EMA;
    if ( str == "BAR_SEQ_DOWN" )    return UiNodeType::BAR_SEQ_DOWN;
    if ( str == "BAR_SEQ_UP" )    return UiNodeType::BAR_SEQ_UP;
    if ( str == "BOLL" )   return UiNodeType::BOLL;
    if ( str == "COUNTER" )   return UiNodeType::COUNTER;
    if ( str == "CROSS" )    return UiNodeType::CROSS;
    if ( str == "PSAR" )    return UiNodeType::PSAR;
    if ( str == "TRADE" )    return UiNodeType::TRADE;
    if ( str == "TREND" )    return UiNodeType::TREND;
    if ( str == "TRIX" )    return UiNodeType::TRIX;
    if ( str == "VWAP" )   return UiNodeType::VWAP;
    if ( str == "WMA" )    return UiNodeType::WMA;
    if ( str == "SMA" )    return UiNodeType::SMA;
    return UiNodeType::BAR_SEQ_DOWN;
}

NodeType INode::stringToType(const std::string& str) {
    if ( str == "EMA" )    return NodeType::EMA;
    if ( str == "BAR_SEQ_DOWN" )    return NodeType::BAR_SEQ_DOWN;
    if ( str == "BAR_SEQ_UP" )    return NodeType::BAR_SEQ_UP;
    if ( str == "BOLL" )   return NodeType::BOLL;
    if ( str == "COUNTER" )   return NodeType::COUNTER;
    if ( str == "CROSS" )    return NodeType::CROSS;
    if ( str == "PSAR" )    return NodeType::PSAR;
    if ( str == "TRADE" )    return NodeType::TRADE;
    if ( str == "TREND" )    return NodeType::TREND;
    if ( str == "TRIX" )    return NodeType::TRIX;
    if ( str == "VWAP" )   return NodeType::VWAP;
    if ( str == "WMA" )    return NodeType::WMA;
    if ( str == "SMA" )    return NodeType::SMA;
    return NodeType::BAR_SEQ_DOWN;
}

void INode::setPosition(ImVec2 newPos) {
    _pos = newPos;
}
