//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include <implot.h>
#include <imgui_internal.h>
#include "MainMenuBar.h"
#include "../Editor.h"
#include <fmt/format.h>

MainMenuBar::MainMenuBar(Editor *editor) : Widget(editor)
{
    _title                  = "MainMenuBar";
    _is_window              = false;
}

void MainMenuBar::updateAlways(float dt)
{
    PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(GetPadding(), GetPadding()));
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    PushStyleColor(ImGuiCol_MenuBarBg,Editor::broker_black);

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
            if (ImGui::MenuItem("Data downloader", "CTRL+D",&_show_downloader)){}
            if (ImGui::MenuItem("Charts", "CTRL+G",&_show_charts)){}
            if (ImGui::MenuItem("Indicators", "",&_show_indicators)){}

            ImGui::MenuItem("ImGui Metrics", nullptr, &_imgui_metrics);
            ImGui::MenuItem("ImGui Style",   nullptr, &_imgui_style);
            ImGui::MenuItem("ImGui Demo",    nullptr, &_imgui_demo);
            ImGui::MenuItem("ImPlot Demo",    nullptr, &_implot_demo);
            ImGui::MenuItem("Show tabbars on views", "", &_show_tabbars);

            static int ui_num = 1;

//            if(ImGui::InputInt("ui number",&ui_num)){}

            if(ImGui::Button("Save UI")){
                std::string _filePath = fmt::format("ui_num_{}",ui_num);
                ImGui::SaveIniSettingsToDisk(_filePath.c_str());
            }

//            if(ImGui::Button("Load UI")){
//                std::string _filePath = fmt::format("ui_num_{}",ui_num);
//                //TODO:: this do not work properly here need to be called before the first newFrame call.
//                ImGui::LoadIniSettingsFromDisk(_filePath.c_str());
//            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &_showAboutWindow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //update editor
    _editor->showDataLoader(_show_downloader);
    _editor->showCharts(_show_charts);
    _editor->showIndicators(_show_indicators);
    _editor->showTabBars(_show_tabbars);

    if (_imgui_metrics)
    {
        ImGui::ShowMetricsWindow();
    }

    if (_imgui_style)
    {
        ImGui::Begin("Style Editor", nullptr, ImGuiWindowFlags_NoDocking);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    if (_imgui_demo)
    {
        ImGui::ShowDemoWindow(&_imgui_demo);
    }

    if (_implot_demo)
    {
        ImPlot::ShowDemoWindow(&_implot_demo);
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

