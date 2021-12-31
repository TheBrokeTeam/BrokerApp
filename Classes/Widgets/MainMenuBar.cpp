//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include <implot.h>
#include <imgui_internal.h>
#include "MainMenuBar.h"
#include "../Editor.h"
#include "DataLoader.h"
#include "SimulationController.h"
#include "Chart.h"
#include "ProfitAndLosses.h"
#include <fmt/format.h>

MainMenuBar::MainMenuBar(Context* context) : Widget(context)
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
            if (ImGui::MenuItem("Data downloader", "CTRL+D",&(getContext()->getWidget<DataLoader>()->GetVisible()))){}
            if (ImGui::MenuItem("Simulator", "CTRL+S",&(getContext()->getWidget<SimulationController>()->GetVisible()))){}
            if (ImGui::MenuItem("Chart", "CTRL+G",&(getContext()->getWidget<Chart>()->GetVisible()))){}
            if (ImGui::MenuItem("Indicators", "",&(getContext()->getWidget<Indicators>()->GetVisible()))){}
            if (ImGui::MenuItem("PnL", "",&(getContext()->getWidget<ProfitAndLosses>()->GetVisible()))){}


            ImGui::MenuItem("ImGui Metrics", nullptr, &_imgui_metrics);
            ImGui::MenuItem("ImGui Style",   nullptr, &_imgui_style);
            ImGui::MenuItem("ImGui Demo",    nullptr, &_imgui_demo);
            ImGui::MenuItem("ImPlot Demo",    nullptr, &_implot_demo);
            ImGui::MenuItem("Show tabbars on views", "", &_show_tabbars);

            static int ui_num = 1;
            if(ImGui::Button("Save UI")){
                std::string _filePath = fmt::format("ui_num_{}",ui_num);
                ImGui::SaveIniSettingsToDisk(_filePath.c_str());
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &_showAboutWindow);
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //TODO:: remove this on release
    //update editor develop function
    getContext()->getEditor()->showTabBars(_show_tabbars);

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

