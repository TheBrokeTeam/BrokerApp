//
// Created by Arthur Abel Motelevicz on 22/12/21.
//

#include "DataLoader.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Editor.h"

namespace _DataLoader
{
    static bool show_downloader = false;
    static bool show_candle_graph = false;
    static bool show_study_chart = false;
    static bool show_indicator_controller = false;
    static bool showShortcutsWindow = false;
    static bool showAboutWindow     = false;
    static bool imgui_metrics         = false;
    static bool imgui_style           = false;
    static bool imgui_demo            = false;
    static bool implot_demo            = false;
}

DataLoader::DataLoader(Editor *editor) : Widget(editor)
{
    _title                  = "Data Loader";
    _is_window              = true;
}

void DataLoader::updateVisible(float dt)
{
    static char buff[8] = "ETHUSDT";
    ImGui::SetNextItemWidth(200);
    if (ImGui::InputText("##Symbol",buff,8,ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CharsUppercase)) {
        _info.fetchSymbol = buff;
    }

    ImGui::SetNextItemWidth(100);

    static int interval = 3;
    if (ImGui::Combo("Time Interval", &interval, "1m\0""3m\0""5m\0""15m\0""30m\0""1h\0""2h\0""4h\0""6h\0""8h\0""12h\0""1d\0""3d\0""1w\0""1mo\0")) {
        static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                                "2h", "4h", "6h", "8h", "12h", "1d",
                                                "3d", "1w", "1mo"};
        _info.fetchInterVal = interval_str[interval];
    }

    ImGui::SetNextItemWidth(100);

    static int yr = 3;
    if (ImGui::Combo("Year", &yr, "2018\0""2019\0""2020\0""2021\0")) {
        static const std::string yearArr[]{"2018","2019","2020","2021"};
        _info.fetchYear = yearArr[yr];
    }

    ImGui::SetNextItemWidth(100);

    static int mo = 0;
    if (ImGui::Combo("Month", &mo, "01\0""02\0""03\0""04\0""05\0""06\0""07\0""08\0""09\0""10\0""11\0""12\0")) {
        static const std::string mothArr[]{"01","02","03","04","05","06","07","08","09","10","11","12"};
        _info.fetchMonth = mothArr[mo];
    }

    if (ImGui::Button("Fetch")) {
        puts("Clicou no botão fetch!!!");
        Symbol symbol(_info.fetchSymbol);
        symbol.setTimeInterval(Symbol::Interval(interval));

        auto ticker = _context->loadSymbol(symbol);
        _editor->addChartWidget(ticker);
    }

//    auto info = _editor->getTexture(Editor::Icons::indicator_ma);
//    ImGui::Begin("OpenGL Texture Text");
//    ImGui::Text("pointer = %p", info.my_image_texture);
//    ImGui::Text("size = %d x %d", info.my_image_width, info.my_image_height);
//    ImGui::Image((void*)(intptr_t)info.my_image_texture, ImVec2(info.my_image_width, info.my_image_height));
//    ImGui::End();
}

int DataLoader::getWindowFlags() {
//    ImGui::SetNextWindowPos(ImVec2(0,35));
    return  ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse            ;
            //            ImGuiWindowFlags_NoMove;
}

void DataLoader::onPushStyleVar() {
    ImGui::SetNextWindowSize(ImVec2(200,ImGui::GetMainViewport()->Size.y));
    PushStyleColor(ImGuiCol_WindowBg,Editor::broker_dark_grey);
}
