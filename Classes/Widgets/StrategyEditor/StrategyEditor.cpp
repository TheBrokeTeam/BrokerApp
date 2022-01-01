//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#include "StrategyEditor.h"
#include "../../Editor.h"
#include <imnodes.h>

StrategyEditor::StrategyEditor(Context* context) : Widget(context) {
    _title                  = "Strategy editor";
    _is_window              = true;

    _nodes.push_back(TestNode());
    _nodes.push_back(TestNode());

}

void StrategyEditor::updateVisible(float dt) {
    Widget::updateVisible(dt);

    ImNodes::BeginNodeEditor();

    for(auto& n : _nodes){
        n.render();
    }

    for (int i = 0; i < links.size(); ++i)
    {
        const std::pair<int, int> p = links[i];
        // in this case, we just use the array index of the link
        // as the unique identifier
        ImNodes::Link(i, p.first, p.second);
    }

    ImNodes::EndNodeEditor();

    int start_attr, end_attr;
    if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
    {
        links.push_back(std::make_pair(start_attr, end_attr));
    }
}

void StrategyEditor::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}