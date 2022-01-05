//
// Created by Luiz Veloso on 31/12/21.
//

#include <iomanip>
#include "StockList.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"

StockList::StockList(Context *context) : Widget(context)
{
    _title                  = "Stock List";
    _is_window              = true;
}

void StockList::cell()
{ //StockInfo info){

    ImGui::TextColored(Editor::broker_white,"ETHBTC");
    ImGui::TextColored(Editor::broker_light_grey,"Etherium BTC");
    ImGui::TableNextColumn();
    ImGui::TextColored(Editor::broker_white,"U$");
    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"4000");
    double relative = -1.1;

    std::stringstream ss;

    std::string relativePrice = ss.str();

    ImVec4 relativePriceColor;
    std::string sign;

    if (relative < 0)
    {
        relativePriceColor = Editor::broker_red;
        sign = "-";
    } else if (relative == 0) {
        relativePriceColor = Editor::broker_yellow;
        sign = "";
    } else {
        relativePriceColor = Editor::broker_green;
        sign = "+";
    }
    relative = relative * 100;
    ss << std::fixed << sign << std::setprecision(2) << (relative) << "%";
    std::string relativeString = ss.str();


    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetColumnWidth() - ImGui::CalcTextSize(relativeString.c_str()).x);
    ImGui::TextColored(relativePriceColor, "%s", relativeString.c_str());
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
    auto info = getContext()->getEditor()->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        SetVisible(false);
    }

    ImGui::Separator();

    ImGui::Spacing();


    ImGui::PushStyleVar(ImGuiStyleVar_CellPadding, ImVec2(5, 5));
    //ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));

    int tableFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_PadOuterX |
                                  ImGuiTableFlags_ScrollY;
    if (ImGui::BeginTable("##table2", 2, tableFlags))
    {
        ImGui::TableSetupColumn("Asset", ImGuiTableColumnFlags_WidthStretch);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);

        for (int row = 0; row < 30; row++)
        {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            StockList::cell();
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleVar();


}


void StockList::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
