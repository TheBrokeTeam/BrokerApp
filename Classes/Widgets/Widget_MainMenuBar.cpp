//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include <implot.h>
#include "Widget_MainMenuBar.h"
#include "../Editor.h"

namespace _Widget_MainMenuBar
{
    static bool show_downloader = true;
    static bool show_charts = true;
    static bool show_study_chart = false;
    static bool show_indicator_controller = false;
    static bool showShortcutsWindow = false;
    static bool showAboutWindow     = false;
    static bool imgui_metrics         = false;
    static bool imgui_style           = false;
    static bool imgui_demo            = false;
    static bool implot_demo            = false;
}

Widget_MainMenuBar::Widget_MainMenuBar(Editor *editor) : Widget(editor)
{
    _title                  = "MainMenuBar";
    _is_window              = false;
}

void Widget_MainMenuBar::updateAlways(float dt)
{
//    puts("updateAlways");
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(GetPadding(), GetPadding()));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

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
            if (ImGui::MenuItem("Data Loader", "CTRL+D",&_Widget_MainMenuBar::show_downloader)){}
            if (ImGui::MenuItem("Charts", "CTRL+G",&_Widget_MainMenuBar::show_charts)){}
            if (ImGui::MenuItem("Indicators", "",&_Widget_MainMenuBar::show_indicator_controller)){}

            ImGui::MenuItem("ImGui Metrics", nullptr, &_Widget_MainMenuBar::imgui_metrics);
            ImGui::MenuItem("ImGui Style",   nullptr, &_Widget_MainMenuBar::imgui_style);
            ImGui::MenuItem("ImGui Demo",    nullptr, &_Widget_MainMenuBar::imgui_demo);
            ImGui::MenuItem("ImPlot Demo",    nullptr, &_Widget_MainMenuBar::implot_demo);

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &_Widget_MainMenuBar::showAboutWindow);
            ImGui::MenuItem("Shortcuts & Input Reference", "Ctrl+P", &_Widget_MainMenuBar::showShortcutsWindow);
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    ImGui::PopStyleVar(2);

    //update editor
    _editor->showDataLoader(_Widget_MainMenuBar::show_downloader);
    _editor->showCharts(_Widget_MainMenuBar::show_charts);

    if (_Widget_MainMenuBar::imgui_metrics)
    {
        ImGui::ShowMetricsWindow();
    }

    if (_Widget_MainMenuBar::imgui_style)
    {
        ImGui::Begin("Style Editor", nullptr, ImGuiWindowFlags_NoDocking);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    if (_Widget_MainMenuBar::imgui_demo)
    {
        ImGui::ShowDemoWindow(&_Widget_MainMenuBar::imgui_demo);
    }

    if (_Widget_MainMenuBar::implot_demo)
    {
        ImPlot::ShowDemoWindow(&_Widget_MainMenuBar::implot_demo);
    }
}

void Widget_MainMenuBar::updateVisible(float dt) {
    puts("updateVisible");
}

void Widget_MainMenuBar::onShow() {
    puts("onShow");
}

void Widget_MainMenuBar::onHide() {
    puts("onHide");
}

