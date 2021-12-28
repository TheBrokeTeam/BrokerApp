//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#include "DataLoader.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"

DataLoader::DataLoader(Editor *editor) : Widget(editor)
{
    _title                  = "Data Loader";
    _is_window              = true;
}

void DataLoader::updateVisible(float dt)
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

    ImGui::TextColored(Editor::broker_white,"Data downloader");
    ImGui::SameLine();

    //change the background of close button
    PushStyleColor(ImGuiCol_Button,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_clear);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_clear);

    //adding the close button
    auto info = _editor->getTexture(Editor::Icons::close_window);
    ImGui::SetCursorPosX( ImGui::GetWindowWidth() - info.my_image_width*2);
    if(ImGui::ImageButton((void*)(intptr_t)info.my_image_texture,ImVec2(info.my_image_width,info.my_image_height))){
        _editor->showDataLoader(false);
    }

    ImGui::Separator();

    ImGui::Spacing();
//    ImGui::Dummy(ImVec2(200,20));

    //change background from other buttons
    PushStyleColor(ImGuiCol_Button,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_white);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_white);

    static char buff[8] = "ETHUSDT";
    ImGui::SetNextItemWidth(200);
    if (ImGui::InputText("##Symbol",buff,8,ImGuiInputTextFlags_CharsUppercase)) {
        _info.fetchSymbol = buff;
    }

    ImGui::SetNextItemWidth(100);

    static int interval = 3;

    if (ImGui::Combo("##intervalid", &interval, "1m\0""3m\0""5m\0""15m\0""30m\0""1h\0""2h\0""4h\0""6h\0""8h\0""12h\0""1d\0""3d\0""1w\0""1mo\0")) {
        //change color text
        PushStyleColor(ImGuiCol_Text,Editor::broker_black);
        static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                                "2h", "4h", "6h", "8h", "12h", "1d",
                                                "3d", "1w", "1mo"};
        _info.fetchInterVal = interval_str[interval];
    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Interval");

    ImGui::SetNextItemWidth(100);

    static int yr = 3;
    if (ImGui::Combo("##YearId", &yr, "2018\0""2019\0""2020\0""2021\0")) {
        static const std::string yearArr[]{"2018","2019","2020","2021"};
        _info.fetchYear = yearArr[yr];
    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Year");

    ImGui::SetNextItemWidth(100);

    static int mo = 0;
    if (ImGui::Combo("##MonthId", &mo, "01\0""02\0""03\0""04\0""05\0""06\0""07\0""08\0""09\0""10\0""11\0""12\0")) {
        static const std::string mothArr[]{"01","02","03","04","05","06","07","08","09","10","11","12"};
        _info.fetchMonth = mothArr[mo];
    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Month");

    ImGui::Dummy(ImVec2(200,30));

    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Download",ImVec2(200,50))) {
        puts("Clicou no botão fetch!!!");
        Symbol symbol(_info.fetchSymbol);
        symbol.setTimeInterval(Symbol::Interval(interval));

        //TODO:: the ticker should  be created by charts widget
        auto ticker = getContext()->loadSymbol(symbol);
        _editor->addChartWidget(ticker);
    }
}

int DataLoader::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void DataLoader::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
