//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#include "SocketStreamController.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"

SocketStreamController::SocketStreamController(Context* context) : Widget(context)
{
    _title = "Downloader";
    _is_window = true;
}

void SocketStreamController::updateVisible(float dt)
{
    Widget::updateVisible(dt);

    //change color text
    PushStyleColor(ImGuiCol_Text,Editor::broker_black);

    //change background of frames
    PushStyleColor(ImGuiCol_FrameBg,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_FrameBgHovered,Editor::broker_white);

    //change background of items on combos
    PushStyleColor(ImGuiCol_PopupBg,Editor::broker_white);

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_white);

    static char buff[8] = "ETHUSDT";
    ImGui::SetNextItemWidth(200);
    if (ImGui::InputText("##Symbol",buff,8,ImGuiInputTextFlags_CharsUppercase)) {
        _symbolName = buff;
    }

    ImGui::SetNextItemWidth(80);

    static int interval = 0;

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Interval");

    ImGui::SetNextItemWidth(110);

    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Open Stream",ImVec2(200,50))) {
        _symbol =   Symbol(_symbolName,"1s",0,0);
        getContext()->openSymbolStream(_symbol);
    }

    if (ImGui::Button("Close Stream",ImVec2(200,50))) {
        getContext()->closeSymbolStream(_symbol);
    }
}

int SocketStreamController::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void SocketStreamController::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
