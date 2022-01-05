//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "BackTestingContext.h"

#include <curl/curl.h>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <fmt/format.h>
#include <zip_file.hpp>
#include <rapidcsv.h>
#include "../Tickables/Indicators/SMA.h"
#include "../Tickables/Indicators/Bollinger.h"

#include "../Widgets/MainMenuBar.h"
#include "../Widgets/DownloaderView.h"
#include "../Widgets/SimulationController.h"
#include "../Widgets/ProfitAndLossesView.h"
#include "../Widgets/ChartView.h"
#include "../Widgets/StrategyEditor/StrategyEditor.h"
#include "../Tickables/Strategies/IndicatorToChartExample.h"
#include "../Nodes/SMANode.h"
#include "../Nodes/TestAddNode.h"
#include "../Nodes/TestMultiplyNode.h"
#include "../Nodes/TestResultNode.h"
#include "../Nodes/CrossNode.h"

#include "../Nodes/Add.h"
#include "../Nodes/ShowOutput.h"



static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                        "2h", "4h", "6h", "8h", "12h", "1d",
                                        "3d", "1w", "1mo"};

BackTestingContext::BackTestingContext(Editor *editor) : Context(editor) {

}

void BackTestingContext::initialize() {

    // Initialize the context
    _widgets.emplace_back(std::make_shared<MainMenuBar>(this));
    _widgets.emplace_back(std::make_shared<DownloaderView>(this));
    _widgets.emplace_back(std::make_shared<SimulationController>(this));
    _widgets.emplace_back(std::make_shared<ChartView>(this));
    _widgets.emplace_back(std::make_shared<ProfitAndLossesView>(this));
    _widgets.emplace_back(std::make_shared<IndicatorsView>(this));
    _widgets.emplace_back(std::make_shared<StrategyEditor>(this));

    getWidget<ProfitAndLossesView>()->SetVisible(false);

    getWidget<IndicatorsView>()->setTrashCallback([this](){
        for(auto& i : _indicators){
            if(_ticker->removeTickable(i.get()))
                puts("indicator removed successfully");
        }
        _indicators.clear();

        getWidget<StrategyEditor>()->clear();
        _nodes.clear();

//        //create test strategy for tests
//        _ticker->removeTickable(_strategy.get());
//
//        _strategy.reset();
//        _strategy = std::make_shared<IndicatorToChartExample>(_ticker.get());
//        _ticker->addStrategy(_strategy.get());
//        getWidget<ProfitAndLossesView>()->setStrategyTest(_strategy);
    });

}

Ticker* BackTestingContext::loadSymbol(const Symbol& symbol) {

    std::string filename = "data.zip";
    auto url = build_url(symbol.getName(),symbol.year,symbol.month,interval_str[int(symbol.getTimeInterval())]);

    if(!dataAlreadyExists(symbol))
        auto resp = download_file(url,filename);

    _ticker.reset();
    _ticker = std::make_shared<Ticker>(this,symbol);

//    //create test strategy for tests
//    _strategy.reset();
//    _strategy = std::make_shared<IndicatorToChartExample>(_ticker.get());
//    _ticker->addStrategy(_strategy.get());
//
//    getWidget<ProfitAndLossesView>()->setStrategyTest(_strategy);

   _data.clear();
    _data = loadCsv(symbol);

    auto chart = getWidget<ChartView>();
    chart->addChart(std::make_shared<CandleChart>(this,_ticker.get()));
    loadTicker();

    return _ticker.get();

}

BackTestingContext::DownloadResponse BackTestingContext::download_file(std::string url, std::string filename) {
    bool success = false;
    CURL *curl;
    FILE *fp;
    CURLcode res;
    curl = curl_easy_init();
    DownloadResponse response;
    if (curl) {
        fp = fopen(filename.c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        //TODO:: I dont know if this is ok based on these comments:
        //https://stackoverflow.com/questions/25540547/how-to-download-a-zip-file-from-server-using-curl-in-c

        curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
        //###########################################################

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        if (res == 0)
            success = true;
        curl_easy_cleanup(curl);
        fclose(fp);

        response.success = success;

        if(!response.success)
            return response;

        //TODO::remove the unzip from here
        miniz_cpp::zip_file file(filename);
        file.extractall("./");

        namespace fs = std::filesystem;

        fs::remove(filename);

        response.extractedFileName = file.getinfo(0).filename;
    }
    return response;
}

std::string BackTestingContext::build_url(std::string symbol, std::string year, std::string month, std::string interval) {

    return fmt::format("https://data.binance.vision/data/spot/monthly/klines/{}/{}/{}-{}-{}-{}.zip",
                       symbol,
                       interval,
                       symbol,
                       interval,
                       year,
                       month
    );
}

bool BackTestingContext::dataAlreadyExists(const Symbol &symbol) {
    return std::filesystem::exists(getFilePathFromSymbol(symbol));
}


std::vector<TickData> BackTestingContext::loadCsv(const Symbol& symbol){

    std::vector<TickData> output;
    auto filePath = getFilePathFromSymbol(symbol);

    std::cout << "Start Loading file: " << filePath << std::endl;

    rapidcsv::Document doc(filePath, rapidcsv::LabelParams(-1,-1));

    for(int i = 0; i < doc.GetRowCount(); i++)
    {
        TickData data_open;
        TickData data_high;
        TickData data_low;
        TickData data_close;

        //converting ms to sec and add simulated time for the sub tick on the bars
        double timeInSec = doc.GetCell<long>(0,i)/1000.0;
        data_open.time  = timeInSec;
        data_high.time  = timeInSec + symbol.getTimeIntervalInMinutes()*0.25 * 60;
        data_low.time  = timeInSec + symbol.getTimeIntervalInMinutes()*0.5* 60;
        data_close.time  = timeInSec + symbol.getTimeIntervalInMinutes()*60 - 1;

        data_open.price = doc.GetCell<double>(1,i);
        data_high.price = doc.GetCell<double>(2,i);
        data_low.price = doc.GetCell<double>(3,i);
        data_close.price = doc.GetCell<double>(4,i);

        //0.25 volume for each tick
        double volume = doc.GetCell<double>(5,i)*0.25;
        data_open.volume = volume;
        data_high.volume = volume;
        data_low.volume = volume;
        data_close.volume = volume;

        output.push_back(data_open);
        output.push_back(data_high);
        output.push_back(data_low);
        output.push_back(data_close);
    }

    return output;
}

bool BackTestingContext::isSimulating() {
    return _simulating;
}

std::string BackTestingContext::getFilePathFromSymbol(const Symbol& symbol) {

    std::string out = fmt::format("./{}-{}-{}-{}.csv",
            symbol.getName(),
            interval_str[int(symbol.getTimeInterval())],
            symbol.year,
            symbol.month);

    return out;
}

void BackTestingContext::loadTicker() {
    for(auto& d : _data)
        _ticker->tick(d);
}

void BackTestingContext::updateData(float dt) {

    if(!_simulating) return;

    _currentTime += dt*_speed;
    if(_currentTime >= _timeToTick){
        int numberOfTicks = floor(_currentTime/_timeToTick);
        _currentTime = 0;
        for(int i = 0; i < numberOfTicks; i++)
        {
            auto& tickData = _data[_currentIndex++];
            _ticker->tick(tickData);
            if(_currentIndex >= _data.size())
                _simulating = false;
        }
    }
}

void BackTestingContext::startSimulation(Ticker* ticker) {
    //just for tests
    //TODO:: use the ticker parameter
    _ticker->reset();
    _currentIndex = 0;
    _simulating = true;
}

void BackTestingContext::setSimulationSpeed(float speed) {
    _speed = speed*_speedLimit;
}

std::shared_ptr<Indicator> BackTestingContext::loadIndicator(IndicatorsView::CandleIndicatorsTypes type) {

    std::shared_ptr<Indicator> indicator{nullptr};

    switch (type) {
        case IndicatorsView::CandleIndicatorsTypes::SMA:
        {
            std::unique_ptr<SMA> sma = std::make_unique<SMA>(_ticker.get());
            _indicators.push_back(std::move(sma));
            indicator = _indicators.back();
            _ticker->addIndicator(_indicators.back().get());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::BOLL:
        {
            std::unique_ptr<Bollinger> boll = std::make_unique<Bollinger>(_ticker.get());
            _indicators.push_back(std::move(boll));
            indicator = _indicators.back();
            _ticker->addIndicator(_indicators.back().get());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::EMA:
        case IndicatorsView::CandleIndicatorsTypes::WMA:
        case IndicatorsView::CandleIndicatorsTypes::AVL:
        case IndicatorsView::CandleIndicatorsTypes::VWAP:
        case IndicatorsView::CandleIndicatorsTypes::TRIX:
        case IndicatorsView::CandleIndicatorsTypes::SAR :
            _shouldShowLuizPopup = true;
            break;
        default:
            break;
    }

    return indicator;
}

void BackTestingContext::plotIndicators() {
    for(auto& i : _indicators) {
        i->render();
    }

    if(_shouldShowLuizPopup){
        {
            ImGui::OpenPopup("Indicator missing!");
            // Always center this window when appearing
            ImVec2 center = ImGui::GetMainViewport()->GetCenter();
            ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

            if (ImGui::BeginPopupModal("Indicator missing!", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::Text("Hey Luiz, it seems like you are not working too hard.. \nWhat about work on this right now?\n\n");
                ImGui::Separator();

                ImGui::PushStyleColor(ImGuiCol_Button,Editor::broker_light_grey);
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,Editor::broker_dark_grey);
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,Editor::broker_yellow);

                if (ImGui::Button("OK", ImVec2(120, 0))) {
                    _shouldShowLuizPopup = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::PopStyleColor(3);
                ImGui::SetItemDefaultFocus();
                ImGui::EndPopup();
            }
        }
    }
}

void BackTestingContext::plotStrategy() {
//    _strategy->render();
}

void BackTestingContext::plotNodes(float dt){
    for (auto &n : _nodes)
        n->render(dt);
}


//develop phase
void BackTestingContext::showTabBars(bool show) {
    for(auto& w : getWidgets()){
        w->showTabBar(show);
    }
    MainMenuBar::_show_tabbars = show;
}

std::shared_ptr<INode> BackTestingContext::createNode(IndicatorsView::CandleIndicatorsTypes type) {

    std::shared_ptr<INode> node{nullptr};

    switch (type) {
        case IndicatorsView::CandleIndicatorsTypes::SMA:
        {
//            node = std::make_shared<SMANode>();

            /*TODO:: define behavior: there are 2 options
             1) let the strategy and chart independents
             2) make both work as one : if put indicator on the chart the node will appear
                on the editor and the other way around.
            */
//            loadIndicator(type);

//            _nodes.push_back(node);
            auto node = createNode(IndicatorsView::Nodes::SMA);
            getWidget<StrategyEditor>()->addNode(node);
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::BOLL:
        case IndicatorsView::CandleIndicatorsTypes::EMA:
        case IndicatorsView::CandleIndicatorsTypes::WMA:
        case IndicatorsView::CandleIndicatorsTypes::AVL:
        case IndicatorsView::CandleIndicatorsTypes::VWAP:
        case IndicatorsView::CandleIndicatorsTypes::TRIX:
        case IndicatorsView::CandleIndicatorsTypes::SAR :
            _shouldShowLuizPopup = true;
            break;
        default:
            break;
    }

    return node;
}

std::shared_ptr<INode> BackTestingContext::createNode(IndicatorsView::Nodes type) {

    std::shared_ptr<INode> node{nullptr};

    switch (type) {
        case IndicatorsView::Nodes::ADD:
            {
                node = std::make_shared<TestAddNode>();
                _nodes.push_back(node);
            }
            break;
        case IndicatorsView::Nodes::MULTIPLY:
        {
            node = std::make_shared<TestMultiplyNode>();
            _nodes.push_back(node);
        }
            break;
        case IndicatorsView::Nodes::SMA:
        {
            auto smaInd = loadIndicator(IndicatorsView::CandleIndicatorsTypes::SMA);
            node = std::make_shared<SMANode>(smaInd);
            _nodes.push_back(node);
        }
            break;
        case IndicatorsView::Nodes::CROSS:
        {
            node = std::make_shared<CrossNode>();
            _nodes.push_back(node);
        }
            break;
        case IndicatorsView::Nodes::RESULT:
            {
                node = std::make_shared<TestResultNode>();
                _nodes.push_back(node);
            }
            break;
        default:
            break;
    }

    return node;
}

std::shared_ptr<UiNode> BackTestingContext::createNode(std::shared_ptr<graph::Graph<GraphNode>> _graph, NodeType type)
{
    std::shared_ptr<UiNode> node{nullptr};
    switch (type) {
        case NodeType::ADD:
            node = std::make_shared<Add>(_graph);
            break;
        case NodeType::RESULT:
            node = std::make_shared<ShowOutput>(_graph);
            getWidget<StrategyEditor>()->setRootId(node->getId());
            break;
        case NodeType::VALUE:
        default:
            break;
    }

    return node;
}







