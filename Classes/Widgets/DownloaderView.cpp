//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#include "DownloaderView.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"
#include "SubWidgets/DateChooser.h"
#include "SubWidgets/Spinner.h"
#include "SubWidgets/BufferingBar.h"
#include <iostream>
#include <thread>

DownloaderView::DownloaderView(Context* context) : Widget(context)
{
    _title = "Downloader";
    _is_window = true;

    ImGui::SetDateToday(&endDate);
    startDate = endDate;
    startDate.tm_mon = 11;
    startDate.tm_year = 121;

    _info.fetchStartTime = ImGui::GetTimestamp(startDate, true);
    _info.fetchEndTime = ImGui::GetTimestamp(endDate, true);
}

void DownloaderView::updateVisible(float dt)
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
        _info.fetchSymbol = buff;
    }

    ImGui::SetNextItemWidth(80);

    static int interval = 0;

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

    ImGui::SetNextItemWidth(110);

    if(ImGui::DateChooser("##startDate", startDate, "%d/%m/%Y", true)){
        _info.fetchStartTime = ImGui::GetTimestamp(startDate, true);
        std::cout << "Start Date: " << _info.fetchStartTime << std::endl;
    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"Start Date");

    ImGui::SetNextItemWidth(110);

    if(ImGui::DateChooser("##endDate", endDate,  "%d/%m/%Y", true)){
        _info.fetchEndTime = ImGui::GetTimestamp(endDate, true);
        std::cout << "Start Date 2: " << _info.fetchStartTime << std::endl;
        std::cout << "End Date 2: " << _info.fetchEndTime << std::endl;
        showWarning = _info.fetchStartTime >= _info.fetchEndTime;
        if(!showWarning) {
            std::cout << "End Date: " << _info.fetchEndTime << std::endl;
        }

    }

    if(showWarning) {
        ImGui::OpenPopup("End date is wrong");

        // Always center this window when appearing
        ImVec2 center = ImGui::GetMainViewport()->GetCenter();
        ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

        if (ImGui::BeginPopupModal("End date is wrong", NULL, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::Text("\n\nEnd date must be greater than start date\n\n\n");
            ImGui::Separator();

            ImGui::PushStyleColor(ImGuiCol_Button,Editor::broker_light_grey);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_dark_grey);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow);


            if (ImGui::Button("I got it!", ImVec2(120, 0))) {
                ImGui::SetDateToday(&endDate);
                _info.fetchEndTime = ImGui::GetTimestamp(endDate, true);
                showWarning = false;
                ImGui::CloseCurrentPopup();
            }

            ImGui::PopStyleColor(3);
            ImGui::SetItemDefaultFocus();
            ImGui::EndPopup();
        }

    }

    ImGui::SameLine();
    ImGui::TextColored(Editor::broker_white,"End Date");

    const ImVec4 col = ImVec4(0.94f, 0.72f, 0.02f, 1.00f);
    const ImVec4 bg = ImVec4(0.86f, 0.11f, 0.71f, 1.00f);

    ImGui::Dummy(ImVec2(200,10));


    if(getContext()->startSpinner) {
        ImGui::SetCursorPosX(100);
        ImGui::LoadingIndicatorCircle("Waiting", 10, bg, col, 12, 10);
    }

    ImGui::Dummy(ImVec2(200,10));

    PushStyleColor(ImGuiCol_Button,Editor::broker_yellow);
    PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_yellow_active);
    PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow_hover);

    if (ImGui::Button("Download",ImVec2(200,50))) {
        puts("Clicou no botão download!!!");
        getContext()->startFetching = true;
    }

    if(getContext()->startFetching) {
        getContext()->startSpinner = true;
        getContext()->setShouldRender(false);
        std::thread t(fetchingSymbol, _info, getContext());
        t.detach();
    }
}

int DownloaderView::getWindowFlags() {
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse;
}

void DownloaderView::onPushStyleVar() {
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}

void DownloaderView::fetchingSymbol(const FetchInfo& _info, Context* context) {
    Symbol symbol(_info.fetchSymbol, _info.fetchInterVal, _info.fetchStartTime, _info.fetchEndTime);
    context->startFetching = false;

    //TODO:: the ticker should  be created by charts widget
    context->fetchDataSymbol(symbol);
    context->startSpinner = false;
}
