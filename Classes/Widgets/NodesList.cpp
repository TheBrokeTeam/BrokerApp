//
// Created by Arthur Abel Motelevicz on 06/01/22.
//

#include "NodesList.h"
#include "../Editor.h"
#include "../Nodes/UiNodeType.h"

NodesList::NodesList(Context* context) : Widget(context) {

    _title                  = "Nodes";
    _is_window = false;

    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::CROSS));
    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::COUNTER));
    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::BAR_SEQ_UP));
    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::BAR_SEQ_DOWN));
    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::TREND));
    _dragAndDropItems.push_back(DragAndDropNodeItem(UiNodeType::TRADE));
}

void NodesList::updateVisible(float dt) {
//    Widget::updateVisible(dt);
    drawView();
}

void NodesList::drawView() {
    float nodeWidth = 60;
    ImGui::PushStyleColor(ImGuiCol_Button, Editor::broker_black);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, Editor::broker_light_grey);
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, Editor::broker_yellow);

    if(ImGui::BeginChild("NODES_ITEMS", ImVec2(nodeWidth, 400))) {

        //add items to the view
        for (int k = 0; k < _dragAndDropItems.size(); ++k) {

            if (ImGui::BeginChild("##Node item")) {

                auto info = getContext()->getEditor()->getTexture(_dragAndDropItems.at(k).icon);
                ImGui::SetCursorPosX(nodeWidth / 2 - info.my_image_width/2 - 4);
                ImGui::ImageButton((void *) (intptr_t) info.my_image_texture,
                                       ImVec2(info.my_image_width, info.my_image_height));

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                    ImGui::SetDragDropPayload(NodesList::NODES_DRAG_ID, &_dragAndDropItems.at(k).type, sizeof(UiNodeType));
                    auto info = getContext()->getEditor()->getTexture(_dragAndDropItems.at(k).icon);
                    ImGui::Image((void *) (intptr_t) info.my_image_texture,
                                 ImVec2(info.my_image_width * 0.5, info.my_image_height * 0.5));
                    ImGui::EndDragDropSource();
                }

                const bool hovered = ImGui::IsItemHovered();

                if(hovered){
                    ImGui::BeginTooltip();
                    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
                    ImGui::TextUnformatted(_dragAndDropItems.at(k).desc.c_str());
                    ImGui::PopTextWrapPos();
                    ImGui::EndTooltip();
                }


                if (k == (_dragAndDropItems.size() - 1)) {
                    ImGui::Spacing();
                    //change the background of trash button
                    ImGui::PushStyleColor(ImGuiCol_Button, Editor::broker_clear);

                    ImGui::SetCursorPosX(nodeWidth / 2 - info.my_image_width/2 - 4);

                    info = getContext()->getEditor()->getTexture(Editor::Icons::trash);

                    if (ImGui::ImageButton((void *) (intptr_t) info.my_image_texture,
                                           ImVec2(info.my_image_width, info.my_image_height))) {
                        if (_trashCallback)
                            _trashCallback();
                    }

                    ImGui::PopStyleColor();
                }

                ImGui::Spacing();

                ImGui::EndChild();
            }
        }

    }

    ImGui::EndChild();

    ImGui::PopStyleColor(3);

    if (ImGui::BeginDragDropTarget()) {
        if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload(NodesList::NODES_DRAG_ID_REMOVING)) {
            std::shared_ptr<INode> node = *(std::shared_ptr<INode>*) payload->Data;
            //TODO::call remove node on context
            puts("remove node here!");
        }
        ImGui::EndDragDropTarget();
    }
}

std::vector<NodesList::DragAndDropNodeItem> &NodesList::getNodes() {
    return _dragAndDropItems;
}

void NodesList::setTrashCallback(TrashClickCallback callback) {
    _trashCallback = callback;
}
void NodesList::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}


