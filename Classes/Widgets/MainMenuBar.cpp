//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include <implot.h>
#include <imgui_internal.h>
#include "MainMenuBar.h"
#include "../Editor.h"
#include <fmt/format.h>


namespace _MainMenuBar
{
    static bool show_downloader = true;
    static bool show_charts = true;
    static bool show_indicators = true;
    static bool show_tabbars = false;
    static bool showAboutWindow     = false;
    static bool imgui_metrics         = false;
    static bool imgui_style           = false;
    static bool imgui_demo            = false;
    static bool implot_demo            = false;
}

MainMenuBar::MainMenuBar(Editor *editor) : Widget(editor)
{
    _title                  = "MainMenuBar";
    _is_window              = false;
}

void MainMenuBar::updateAlways(float dt)
{
//    puts("updateAlways");
    PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(GetPadding(), GetPadding()));
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleColor(ImGuiCol_MenuBarBg,Editor::broker_dark_grey);

    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Files"))
        {
            if (ImGui::MenuItem("Load CSVs")) {
//                auto paths = openFileDialog(false);
//                _bus->postpone<ui_event::LoadCSVButtonClicked>({paths});
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Data Loader", "CTRL+D",&_MainMenuBar::show_downloader)){}
            if (ImGui::MenuItem("Charts", "CTRL+G",&_MainMenuBar::show_charts)){}
            if (ImGui::MenuItem("Indicators", "",&_MainMenuBar::show_indicators)){}

            ImGui::MenuItem("ImGui Metrics", nullptr, &_MainMenuBar::imgui_metrics);
            ImGui::MenuItem("ImGui Style",   nullptr, &_MainMenuBar::imgui_style);
            ImGui::MenuItem("ImGui Demo",    nullptr, &_MainMenuBar::imgui_demo);
            ImGui::MenuItem("ImPlot Demo",    nullptr, &_MainMenuBar::implot_demo);
            ImGui::MenuItem("Show tabbars on views", "", &_MainMenuBar::show_tabbars);

            static int ui_num = 1;
            if(ImGui::InputInt("ui number",&ui_num)){}

            if(ImGui::Button("Save UI")){
                std::string _filePath = fmt::format("ui_num_{}",ui_num);
                ImGui::SaveIniSettingsToDisk(_filePath.c_str());
            }

            if(ImGui::Button("Load UI")){
                std::string _filePath = fmt::format("ui_num_{}",ui_num);
                ImGui::LoadIniSettingsFromDisk(_filePath.c_str());
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &_MainMenuBar::showAboutWindow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //update editor
    _editor->showDataLoader(_MainMenuBar::show_downloader);
    _editor->showCharts(_MainMenuBar::show_charts);
    _editor->showIndicators(_MainMenuBar::show_indicators);
    _editor->showTabBars(_MainMenuBar::show_tabbars);

    if (_MainMenuBar::imgui_metrics)
    {
        ImGui::ShowMetricsWindow();
    }

    if (_MainMenuBar::imgui_style)
    {
        ImGui::Begin("Style Editor", nullptr, ImGuiWindowFlags_NoDocking);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    if (_MainMenuBar::imgui_demo)
    {
        ImGui::ShowDemoWindow(&_MainMenuBar::imgui_demo);
    }

    if (_MainMenuBar::implot_demo)
    {
        ImPlot::ShowDemoWindow(&_MainMenuBar::implot_demo);
    }
}

void MainMenuBar::updateVisible(float dt) {
    puts("updateVisible");
}

void MainMenuBar::onShow() {
    puts("onShow");
}

void MainMenuBar::onHide() {
    puts("onHide");
}

