//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include <implot.h>
#include <imgui_internal.h>
#include "MainMenuBar.h"
#include "../Editor.h"
#include "DownloaderView.h"
#include "SimulationController.h"
#include "ChartView.h"
#include "ProfitAndLossesView.h"
#include "StockList.h"
#include "StrategyEditor.h"
#include "SocketStreamController.h"
#include <fmt/format.h>
#include "../Contexts/BackTestingContext.h"
#include "../Contexts/LiveContext.h"

MainMenuBar::MainMenuBar(Context* context) : Widget(context)
{
    _title                  = "MainMenuBar";
    _is_window              = false;

    if (dynamic_cast<BackTestingContext*>(context) != nullptr)
    {
        std::cout << "Is backtest" << std::endl;
    }
    else if (dynamic_cast<LiveContext*>(context) != nullptr)
    {
        std::cout << "Is live" << std::endl;
    }
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
            auto contextType = getContext()->getEditor()->getContextType();

            switch (contextType) {
                case  Editor::ContextType::LiveTrade:
                    showLiveContextViews();
                    break;
                case  Editor::ContextType::BackTesting:
                    showBacktestContextViews();
                    break;
                case Editor::ContextType::None:
                default:
                    assert(false && "Broker app context not set!");
                    break;
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Context"))
        {
            if (ImGui::MenuItem("Live trade")) {
                getContext()->getEditor()->loadContext(Editor::ContextType::LiveTrade);
            }

            if (ImGui::MenuItem("Backtesting")) {
                getContext()->getEditor()->loadContext(Editor::ContextType::BackTesting);
            }

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("About", nullptr, &Editor::showAboutWindow);

            ImGui::MenuItem("ImGui Metrics", nullptr,       &Editor::imgui_metrics);
            ImGui::MenuItem("ImGui Style",   nullptr,       &Editor::imgui_style);
            ImGui::MenuItem("ImGui Demo",    nullptr,       &Editor::imgui_demo);
            ImGui::MenuItem("ImPlot Demo",    nullptr,      &Editor::implot_demo);
            ImGui::MenuItem("Show tabbars on views", "",    &Editor::show_tabbars);

            static int ui_num = 1;
            if(ImGui::Button("Save UI")){
                std::string _filePath = fmt::format("ui_num_{}",ui_num);
                ImGui::SaveIniSettingsToDisk(_filePath.c_str());
            }

            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    //TODO:: remove this on release
    //update editor develop function
    getContext()->showTabBars(Editor::show_tabbars);

    if (Editor::imgui_metrics)
    {
        ImGui::ShowMetricsWindow();
    }

    if (Editor::imgui_style)
    {
        ImGui::Begin("Style Editor", nullptr, ImGuiWindowFlags_NoDocking);
        ImGui::ShowStyleEditor();
        ImGui::End();
    }

    if (Editor::imgui_demo)
    {
        ImGui::ShowDemoWindow(&Editor::imgui_demo);
    }

    if (Editor::implot_demo)
    {
        ImPlot::ShowDemoWindow(&Editor::implot_demo);
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

void MainMenuBar::showBacktestContextViews()
{
    if (ImGui::MenuItem("Data downloader", "CTRL+D",&(getContext()->getWidget<DownloaderView>()->GetVisible()))){}
    if (ImGui::MenuItem("Simulator", "CTRL+S",&(getContext()->getWidget<SimulationController>()->GetVisible()))){}
    if (ImGui::MenuItem("Chart View", "CTRL+G",&(getContext()->getWidget<ChartView>()->GetVisible()))){}
    if (ImGui::MenuItem("Indicators View", "",&(getContext()->getWidget<IndicatorsView>()->GetVisible()))){}
    if (ImGui::MenuItem("Strategy View", "",&(getContext()->getWidget<StrategyEditor>()->GetVisible()))){}

    if (ImGui::MenuItem("PnL", "",&(getContext()->getWidget<ProfitAndLossesView>()->GetVisible()))){}
    if (ImGui::MenuItem("Stock List", "",&(getContext()->getWidget<StockList>()->GetVisible()))){}
}

void MainMenuBar::showLiveContextViews() {

    if (ImGui::MenuItem("Stream controller", "CTRL+D",&(getContext()->getWidget<SocketStreamController>()->GetVisible()))){}
    if (ImGui::MenuItem("PnL", "",&(getContext()->getWidget<ProfitAndLossesView>()->GetVisible()))){}
    if (ImGui::MenuItem("Chart View", "CTRL+G",&(getContext()->getWidget<ChartView>()->GetVisible()))){}
    if (ImGui::MenuItem("Indicators View", "",&(getContext()->getWidget<IndicatorsView>()->GetVisible()))){}
}

