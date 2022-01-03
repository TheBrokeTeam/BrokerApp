//
// Created by Luiz Veloso on 31/12/21.
//

#include "StockList.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"

StockList::StockList(Editor *editor) : Widget(editor)
{
    _title                  = "Stock List";
    _is_window              = true;
}

void StockList::cell(StockInfo info){

    ImGui::Separator();
    ImGui::SetNextItemWidth(200);
    ImGui::TextColored(Editor::broker_white,"ETHBTC");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(50);
    ImGui::TextColored(Editor::broker_white,"4.000");
    ImGui::TextColored(Editor::broker_white,"Etherium / Bitcoin");

}

void StockList::updateVisible(float dt)
{
    //change background of window
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    ImGui::TextColored(Editor::broker_white,"Stock List");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_clear);

    //adding the close button
    auto info = _editor->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        _editor->showStockList(false);
    }

    ImGui::Separator();

    ImGui::Spacing();

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_white);

    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(5, 5));
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));

    if (ImGui::BeginTable("##table2", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX | ImGuiTableFlags_ScrollY))
    {
        ImGui::TableSetupColumn("Asset", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);

        for (int row = 0; row < 30; row++)
        {

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::TextColored(Editor::broker_white,"ETHBTC");
            ImGui::TextColored(Editor::broker_light_grey,"Etherium BTC");
            ImGui::TableNextColumn();
            ImGui::TextColored(Editor::broker_white,"U$");
            ImGui::SameLine();
            ImGui::TextColored(Editor::broker_white,"4000");
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();


}


void StockList::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
