//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "INode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "../Widgets/StrategyEditor.h"
#include "UiNodeType.h"
#include <map>
#include <utility>


INode::INode(StrategyEditor* strategyEditor): _nodeEditor(strategyEditor)
{
//    if(!pos.has_value())
//    {
//        ImVec2 mousePos = ImGui::GetMousePos();
//        ImVec2 winPos = ImGui::GetCurrentWindow()->Pos;
//        // TODO::understand why is that
//        //this values was by try and error: ImVec2(8,35)
//        _pos = mousePos - winPos - ImVec2(8,35);
//    } else {
//        _pos = pos.value();
//    }
    _graph = strategyEditor->getGraph();
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

    std::vector<float> position = { this->_pos.x, this->_pos.y };
    BAJson::set(jsonDoc, "position", position);

    BAJson::set(jsonDoc, "_init", this->_init);
    BAJson::set(jsonDoc, "icon", this->_icon);
    BAJson::set(jsonDoc, "isIndicatorNode", this->_isIndicatorNode);
    BAJson::set(jsonDoc, "internalNodes", this->_internalNodes);
    BAJson::set(jsonDoc, "nodeEditor", this->_nodeEditor->getId());

//    std::shared_ptr<graph::Graph<GraphNode>> _graph;
//    std::weak_ptr<Indicator> _indicator;
//    StrategyEditor* _nodeEditor{nullptr};

    return jsonDoc;
}

//std::shared_ptr<INode> INode::Parse(const rapidjson::Value& value) {
//    assert(value.IsObject());
//
//    const rapidjson::Value& jsonPos = value["position"].GetArray();
//    assert(jsonPos.IsArray());
//    float x = jsonPos[0].GetFloat();
//    float y = jsonPos[1].GetFloat();
//    ImVec2 pos = ImVec2(x, y);
//
//    // TODO:
//    const rapidjson::Value& internalNodes = value["internalNodes"].GetArray();
//    assert(internalNodes.IsArray());
//    std::vector<int> vec = std::vector<int>();
//
////    (int id, const std::string& type, const std::string& name, ImVec2 pos, bool init, std::vector<int> internalNodes, bool isIndicatorNode, const std::string& nodeEditor, int icon)
//
//    Ticker* ticker = Ticker(context);
//    StrategyEditor* strategyEditor = StrategyEditor(ticker, context);
//    INode* node = INode(&strategyEditor);
//
////std::shared_ptr<INode> node = new INode(BAJson::getInt(value, "id"),
////                   BAJson::getString(value, "nodeType"),
////                   BAJson::getString(value, "name"),
////                   pos,
////                   BAJson::getBool(value, "_init"),
////                   vec,
////                   BAJson::getBool(value, "isIndicatorNode"),
////                   BAJson::getString(value, "nodeEditor"),
////                   BAJson::getInt(value, "icon")
////                   )
//}

//INode::INode(int id, const std::string& type, const std::string& name, ImVec2 pos, bool init, std::vector<int> internalNodes, bool isIndicatorNode, const std::string& nodeEditor, int icon) {
//    this->_id = id;
//    this->_type = stringToType(type);
//    this->_name = name;
//    this->_pos = pos;
//    this->_init = init;
//    this->_internalNodes = std::move(internalNodes);
//    this->_isIndicatorNode = isIndicatorNode;
//    this->_icon = icon;
//
//    //    this->_nodeEditor = StrategyEditor();
//}

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