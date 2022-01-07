//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "StrategyEditor.h"
#include "../../Editor.h"
#include <imnodes.h>
#include "../../Nodes/Add.h"

// User callback
void mini_map_node_hovering_callback(int node_id, void* user_data)
{
    ImGui::SetTooltip("This is node %d", node_id);
}

StrategyEditor::StrategyEditor(Context* context) : Widget(context) {
    _title                  = "Strategy editor";
    _is_window              = true;
    _graph = std::make_shared<graph::Graph<GraphNode>>();
    _nodesList = std::make_unique<NodesList>(context);

    _nodesList->setTrashCallback([this](){
        clear();
    });
}

void StrategyEditor::updateVisible(float dt) {
    Widget::updateVisible(dt);

    _nodesList->updateVisible(dt);

    ImGui::SameLine();

    ImNodes::PushColorStyle(ImNodesCol_Link, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_LinkHovered, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_hover));
    ImNodes::PushColorStyle(ImNodesCol_LinkSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::PushColorStyle(ImNodesCol_MiniMapLink, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow_active));
    ImNodes::PushColorStyle(ImNodesCol_MiniMapLinkSelected, ImGui::ColorConvertFloat4ToU32(Editor::broker_yellow));

    ImNodes::BeginNodeEditor();

    for (auto &n : _uiNodes)
        n->render(dt);

    for (const auto& edge : _graph->edges())
    {
        // If edge doesn't start at value, then it's an internal edge, i.e.
        // an edge which links a node's operation to its input. We don't
        // want to render node internals with visible links.
        if (_graph->node(edge.from).type != NodeType::VALUE)
            continue;

        ImNodes::Link(edge.id, edge.from, edge.to);
    }

    ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight, mini_map_node_hovering_callback);
    ImNodes::EndNodeEditor();
    if (ImGui::BeginDragDropTarget()) {

        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(NodesList::NODES_DRAG_ID)) {
            UiNodeType type = *(UiNodeType *) payload->Data;
            auto node = getContext()->createNode(_graph,type);
            if(node)
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
        const NodeType start_type = _graph->node(start_attr).type;
        const NodeType end_type = _graph->node(end_attr).type;

        const bool valid_link = start_type != end_type && _graph->num_edges_from_node(end_attr) == 0;
        if (valid_link)
        {
            // Ensure the edge is always directed from the value to
            // whatever produces the value
            if (start_type != NodeType::VALUE)
            {
                std::swap(start_attr, end_attr);
            }
            _graph->insert_edge(start_attr, end_attr);
        }
    }

    // Handle deleted links
    int link_id;
    if (ImNodes::IsLinkDestroyed(&link_id))
    {
        _graph->erase_edge(link_id);
    }

    {
        const int num_selected = ImNodes::NumSelectedLinks();
        if (num_selected > 0 && ImGui::IsKeyReleased(GLFW_KEY_X))
        {
            static std::vector<int> selected_links;
            selected_links.resize(static_cast<size_t>(num_selected));
            ImNodes::GetSelectedLinks(selected_links.data());
            for (const int edge_id : selected_links)
            {
                _graph->erase_edge(edge_id);
            }
        }
    }

    {
        const int num_selected = ImNodes::NumSelectedNodes();
        if (num_selected > 0 && ImGui::IsKeyReleased(GLFW_KEY_X))
        {
            static std::vector<int> selected_nodes;
            selected_nodes.resize(static_cast<size_t>(num_selected));
            ImNodes::GetSelectedNodes(selected_nodes.data());
            for (const int node_id : selected_nodes)
            {
                deleteUiNodeFromFromList(node_id);
            }
        }
    }

    for(auto id : _rootNodes) {
        if(_graph->node(id).owner->getRootNodeConnectionsNumber() > 0)
            evaluateGraph(id);
    }
}

void StrategyEditor::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void StrategyEditor::addNode(std::shared_ptr<INode> newNode) {
    _uiNodes.push_back(newNode);
}

void StrategyEditor::clear() {
    auto copyNodes = _uiNodes;
    for(auto n : copyNodes){
        if(!n->getIsIndicatorNode())
            deleteUiNodeFromFromList(n->getId(),false);
    }
}

void StrategyEditor::evaluateGraph(int id) {
    std::stack<int> postorder;
    dfs_traverse(
            *_graph, id, [&postorder](const int node_id) -> void {
                postorder.push(node_id);
            });

    std::stack<float> value_stack;
    while (!postorder.empty()) {
        const int id = postorder.top();
        postorder.pop();
        const GraphNode node = _graph->node(id);

        if (node.owner) {
            node.owner->handleStack(value_stack);
        } else {
            // If the edge does not have an edge connecting to another node, then just use the value
            // at this node. It means the node's input pin has not been connected to anything and
            // the value comes from the node's UI.
            if (_graph->num_edges_from_node(id) == 0ull)
                value_stack.push(node.value);
        }
    }
}

void StrategyEditor::removeRootId(int id) {
    for(auto it = _rootNodes.begin(); it != _rootNodes.end(); it++){
        if((*it) == id) {
            _rootNodes.erase(it);
            return;
        }
    }
}

 std::shared_ptr<INode> StrategyEditor::getNodeFromId(int id){

    std::shared_ptr<INode> node{nullptr};
    for(auto it = _uiNodes.begin(); it != _uiNodes.end(); it++){
        if((*it)->getId() == id) {
            node = (*it);
            break;
        }
    }

    return node;
}

void StrategyEditor::addRootId(int id) {
    _rootNodes.push_back(id);
}

const std::shared_ptr<graph::Graph<GraphNode>> &StrategyEditor::getGraph() {
    return _graph;
}

void StrategyEditor::deleteUiNodeFromFromList(int id,bool shouldRemoveIndicator) {

    std::shared_ptr<INode> node{nullptr};
    for(auto it = _uiNodes.begin(); it != _uiNodes.end(); it++){
        if((*it)->getId() == id) {

            //remove indicator if it's an indicator node
            if((*it)->getIsIndicatorNode() && shouldRemoveIndicator)
                if(auto ind = (*it)->getIndicator())
                    getContext()->removeIndicator(ind,false);
                else
                    assert(false);

            //delete from root ids if needed
            removeRootId(id);

            _uiNodes.erase(it);
            break;
        }
    }
}

void StrategyEditor::removeNodeIndicator(std::shared_ptr<Indicator> indicator) {
    for(auto it = _uiNodes.begin(); it != _uiNodes.end(); it++) {
        //remove indicator if it's an indicator node
        if ((*it)->getIsIndicatorNode()) {
            if ((*it)->getIndicator()->getId() == indicator->getId()) {
                deleteUiNodeFromFromList((*it)->getId(), false);
                break;
            }
        }
    }
}
