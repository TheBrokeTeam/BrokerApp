//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "StrategyEditor.h"
#include "../../Editor.h"
#include <imnodes.h>

// User callback
void mini_map_node_hovering_callback(int node_id, void* user_data)
{
    ImGui::SetTooltip("This is node %d", node_id);
}

StrategyEditor::StrategyEditor(Context* context) : Widget(context) {
    _title                  = "Strategy editor";
    _is_window              = true;
    _graph = std::make_shared<graph::Graph<GraphNode>>();
}

void StrategyEditor::updateVisible(float dt) {
    Widget::updateVisible(dt);

    ImNodes::PushColorStyle(ImNodesCol_Link, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_LinkHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_LinkSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::PushColorStyle(ImNodesCol_MiniMapLink, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_MiniMapLinkSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::BeginNodeEditor();

    for (auto &n : _uiNodes)
        if(auto node = n.lock())
            node->render(dt);

//    getContext()->plotNodes(dt);

    for (int i = 0; i < links.size(); ++i) {
        const std::pair<int, int> p = links[i];
        // in this case, we just use the array index of the link
        // as the unique identifier
        ImNodes::Link(i, p.first, p.second);
    }

    ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight, mini_map_node_hovering_callback, links.data());
    ImNodes::EndNodeEditor();
    if (ImGui::BeginDragDropTarget()) {

        //######################################################
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID)) {
            //indice of dragged item
            int i = *(int *) payload->Data;

            puts("AGORA é a hora de plotar!!!");
            std::weak_ptr<UiNode> node = getContext()->createNode(_graph,NodeType(i));
            if(node.lock())
                _uiNodes.push_back(node);
        }
        ImGui::EndDragDropTarget();
    }

    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();
    ImNodes::PopColorStyle();

    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        links.push_back(std::make_pair(start_attr, end_attr));
    }

    if(!links.empty()){
        for(auto& l: links){
            auto leftNode = getNodeFromLinkId(l.first);
            auto rightNode = getNodeFromLinkId(l.second);
            if(leftNode && rightNode){
                auto result = leftNode->getValueFromId(l.first);
                rightNode->setValueForId(l.second,result);
            }
        }
    }
}

INode* StrategyEditor::getNodeFromLinkId(int id){
    for(auto& n : _nodes){
        if(auto node = n.lock()){
            if(node->hasInput(id)){
                return node.get();
            }
            if(node->hasOutput(id)){
                return node.get();
            }
        }
    }
    return nullptr;
}

void StrategyEditor::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void StrategyEditor::addNode(std::shared_ptr<INode> newNode) {
    std::weak_ptr<INode> node = newNode;
    if(node.lock())
        _nodes.push_back(node);
}

void StrategyEditor::removeNode(std::shared_ptr<INode> node) {
    auto it = _nodes.begin();
    for(int i = 0; i < _nodes.size(); i++) {
        if(it->lock()->getId() == node->getId()) {
            _nodes.erase(it);
            break;
        }
    }
}

void StrategyEditor::clear() {
    _nodes.clear();
    links.clear();
}
