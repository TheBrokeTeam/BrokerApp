//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#include "Indicators.h"
#include "../Editor.h"
#include "../Tickables/Indicators/SMA.h"


Indicators::Indicators(Context* context) : Widget(context) {

    _title                  = "Indicators";
    _is_window = true;

    for(int i = 0; i< _numberOfItems; i++)
        _dragAndDropItems.push_back(DragAndDropIndicatorItem(static_cast<CandleIndicatorsTypes>(i)));
}

void Indicators::updateVisible(float dt) {
    Widget::updateVisible(dt);
    drawView();
}

void Indicators::drawView() {
    PushStyleColor(ImGuiCol_Button, Editor::broker_black);
    PushStyleColor(ImGuiCol_ButtonHovered, Editor::broker_light_grey);
    PushStyleColor(ImGuiCol_ButtonActive, Editor::broker_yellow);

    if(ImGui::BeginChild("INDICATORS_ITEMS", ImVec2(ImGui::GetWindowWidth(), 600))) {

        //add items to the view
        for (int k = 0; k < _dragAndDropItems.size(); ++k) {

            if (ImGui::BeginChild("##indicator item")) {

                ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - 25 - 8);

                ImGui::Button(_dragAndDropItems[k].label.c_str(), ImVec2(50, 30));

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None)) {
                    ImGui::SetDragDropPayload(Indicators::CANDLE_INDICATORS_DRAG_ID, &k, sizeof(int));
                    auto info = getContext()->getEditor()->getTexture(Editor::Icons::indicator_ma);
                    ImGui::Image((void *) (intptr_t) info.my_image_texture,
                                 ImVec2(info.my_image_width * 0.5, info.my_image_height * 0.5));
                    ImGui::EndDragDropSource();
                }

                const bool hovered = ImGui::IsItemHovered();

//            if (hovered) {
//                puts((std::string("Mouse no indicador: ") + _dragAndDropItems[k].label).c_str());
//            }

                //AddC lose button at the end of indicators list
                if (k == (_dragAndDropItems.size() - 1)) {
                    ImGui::Spacing();
                    //change the background of trash button
                    ImGui::PushStyleColor(ImGuiCol_Button, Editor::broker_clear);

                    auto info = getContext()->getEditor()->getTexture(Editor::Icons::trash);

                    ImGui::SetCursorPosX(ImGui::GetWindowWidth() / 2 - info.my_image_width);

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
}


std::vector<Indicators::DragAndDropIndicatorItem> &Indicators::getIndicators() {
    return _dragAndDropItems;
}

void Indicators::setTrashCallback(TrashClickCallback callback) {
    _trashCallback = callback;
}
void Indicators::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}


