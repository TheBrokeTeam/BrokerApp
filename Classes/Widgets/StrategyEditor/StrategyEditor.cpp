//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "StrategyEditor.h"
#include "../../Editor.h"
#include <imnodes.h>
#include "../../Nodes/Add.h"
#include "../../Nodes/ShowOutput.h"


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

    ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight, mini_map_node_hovering_callback, links.data());
    ImNodes::EndNodeEditor();
    if (ImGui::BeginDragDropTarget()) {

        //######################################################
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID)) {
            //indice of dragged item
            int i = *(int *) payload->Data;

            puts("AGORA é a hora de plotar!!!");
            auto node = getContext()->createNode(_graph,NodeType(i));
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
                _graph->erase_node(node_id);
                auto iter = std::find_if(
                        _uiNodes.begin(), _uiNodes.end(), [node_id](std::shared_ptr<UiNode> node) -> bool {
                            return node->getId() == node_id;
                        });
                // Erase any additional internal nodes
                bool found = false;
                switch ((*iter)->type)
                {
                    case UiNodeType::ADD:
                        {
                            auto addNode = dynamic_cast<Add *>(iter->get());
                            _graph->erase_node(addNode->getIdInput1());
                            _graph->erase_node(addNode->getIdInput2());
                            found = true;
                        }
                        break;
                    case UiNodeType::RESULT:
                        {
                            auto addNode = dynamic_cast<ShowOutput*>(iter->get());
                            _graph->erase_node(addNode->getIdInput());
                            found = true;
                            _root_node_id = -1;
                        }
                        break;
                    default:
                        break;
                }
                if(found)
                _uiNodes.erase(iter);

            }
        }
    }
    const float value = _root_node_id != -1 ? evaluateGraph() : 0.0f;
    std::cout << "SAIDA Graph: " << value << std::endl;
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

float StrategyEditor::evaluateGraph() {
    std::stack<int> postorder;
    dfs_traverse(
            *_graph, _root_node_id, [&postorder](const int node_id) -> void {
                postorder.push(node_id);
            });

    std::stack<float> value_stack;
    while (!postorder.empty())
    {
        const int id = postorder.top();
        postorder.pop();
        const GraphNode node = _graph->node(id);

        switch (node.type)
        {
            case NodeType::ADD:
            {
                const float rhs = value_stack.top();
                value_stack.pop();
                const float lhs = value_stack.top();
                value_stack.pop();
                value_stack.push(lhs + rhs);
            }
            break;
            case NodeType::VALUE:
            {
                // If the edge does not have an edge connecting to another node, then just use the value
                // at this node. It means the node's input pin has not been connected to anything and
                // the value comes from the node's UI.
                if (_graph->num_edges_from_node(id) == 0ull)
                {
                    value_stack.push(node.value);
                }
            }
                break;
            default:
                break;
        }
    }

//    // The final output node isn't evaluated in the loop -- instead we just pop
//    // the three values which should be in the stack.
//    assert(value_stack.size() == 3ull);
    assert(value_stack.size() == 1ull);
    const float out = value_stack.top();
//    const int b = static_cast<int>(255.f * clamp(value_stack.top(), 0.f, 1.f) + 0.5f);
//    value_stack.pop();
//    const int g = static_cast<int>(255.f * clamp(value_stack.top(), 0.f, 1.f) + 0.5f);
//    value_stack.pop();
//    const int r = static_cast<int>(255.f * clamp(value_stack.top(), 0.f, 1.f) + 0.5f);
//    value_stack.pop();

    return out;

}

void StrategyEditor::setRootId(int id) {
    _root_node_id =  id;
}
