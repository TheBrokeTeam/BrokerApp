//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#include "INode.h"
#include <imgui.h>
#include <imnodes.h>
#include "../Editor.h"
#include "../Widgets/StrategyEditor.h"
#include "UiNodeType.h"
#include "BrokerColorsImgui.h"


INode::INode(StrategyEditor* strategyEditor):_nodeEditor(strategyEditor)
{
    ImVec2 mousePos = ImGui::GetMousePos();
    ImVec2 winPos = ImGui::GetCurrentWindow()->Pos;
    // TODO::understand why is that
    //this values was by try and error: ImVec2(8,35)
    pos = mousePos - winPos - ImVec2(8,35);
    _graph = strategyEditor->getGraph();
}

void INode::render(float dt) {
    initStyle();
    ImNodes::BeginNode(_id);

    if(!_init) {
        _init = true;
        ImNodes::SetNodeEditorSpacePos(_id,pos);
    }

    ImNodes::BeginNodeTitleBar();
    ImGui::PushStyleColor(ImGuiCol_Text, BrokerColorsImgui::broker_dark_grey);
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

    ImGui::PushStyleColor(ImGuiCol_Text, BrokerColorsImgui::broker_white);
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

    ImNodes::PushColorStyle(ImNodesCol_TitleBar, ImGui::ColorConvertFloat4ToU32(BrokerColorsImgui::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, ImGui::ColorConvertFloat4ToU32(BrokerColorsImgui::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, ImGui::ColorConvertFloat4ToU32(BrokerColorsImgui::broker_yellow));

    ImNodes::PushColorStyle(ImNodesCol_Pin, ImGui::ColorConvertFloat4ToU32(BrokerColorsImgui::broker_yellow));
    ImNodes::PushColorStyle(ImNodesCol_PinHovered, ImGui::ColorConvertFloat4ToU32(BrokerColorsImgui::broker_yellow_hover));
    ImGui::PushStyleColor(ImGuiCol_Text, BrokerColorsImgui::broker_black);

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

