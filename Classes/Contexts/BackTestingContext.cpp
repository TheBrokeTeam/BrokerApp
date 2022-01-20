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
#include "../Tickables/Indicators/EMA.h"
#include "../Tickables/Indicators/TRIX.h"
#include "../Tickables/Indicators/WMA.h"
#include "../Tickables/Indicators/PSAR.h"

#include "../Widgets/MainMenuBar.h"
#include "../Widgets/DownloaderView.h"
#include "../Widgets/SimulationController.h"
#include "../Widgets/ProfitAndLossesView.h"
#include "../Widgets/ChartView.h"
#include "../Widgets/StrategyEditor.h"
#include "../Widgets/StockList.h"
#include "../Tickables/Strategies/IndicatorToChartExample.h"
#include "../Nodes/SMANode.h"
#include "../Nodes/CrossNode.h"
#include "../Nodes/Counter.h"
#include "../Nodes/TradeNode.h"
#include "../Nodes/UpSequenceNode.h"
#include "../Nodes/DownSequenceNode.h"
#include "../Nodes/BarValueNode.h"


static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                        "2h", "4h", "6h", "8h", "12h", "1d",
                                        "3d", "1w", "1mo"};

BackTestingContext::BackTestingContext(Editor *editor) : Context(editor) {
    _ticker.reset();
    _ticker = std::make_shared<Ticker>(this);
}

void BackTestingContext::initialize() {

    // Initialize the context
    _widgets.emplace_back(std::make_shared<MainMenuBar>(this));
    _widgets.emplace_back(std::make_shared<DownloaderView>(this));
    _widgets.emplace_back(std::make_shared<SimulationController>(this));
    _widgets.emplace_back(std::make_shared<ChartView>(this));
    _widgets.emplace_back(std::make_shared<ProfitAndLossesView>(this));
    _widgets.emplace_back(std::make_shared<IndicatorsView>(this));
    _widgets.emplace_back(std::make_shared<StrategyEditor>(_ticker.get(),this));
    _widgets.emplace_back(std::make_shared<StockList>(this));

    getWidget<StockList>()->SetVisible(false);

    getWidget<ProfitAndLossesView>()->SetVisible(false);

    _strategyEditor = getWidget<StrategyEditor>();

    getWidget<IndicatorsView>()->setTrashCallback([this](){
        removeAllIndicators();
//        //create test strategy for tests
//        _ticker->removeTickable(_strategy.get());
//
//        _strategy.reset();
//        _strategy = std::make_shared<IndicatorToChartExample>(_ticker.get());
//        _ticker->addStrategy(_strategy.get());
//        getWidget<ProfitAndLossesView>()->setStrategyTest(_strategy);
    });

    _strategyEditor->setPriority(2);
    _ticker->addTickable(_strategyEditor);
}

void BackTestingContext::loadSymbol(const Symbol& symbol) {

    std::string filename = "data.zip";
    auto url = build_url(symbol.getName(),symbol.year,symbol.month,interval_str[int(symbol.getTimeInterval())]);

    if(!dataAlreadyExists(symbol))
        auto resp = download_file(url,filename);

    _data.clear();
    _data = loadCsv(symbol);

    _ticker->setSymbol(symbol);
    _ticker->reset();
    loadTicker();

    auto chart = getWidget<ChartView>();
    chart->addChart(std::make_shared<CandleChart>(this,_ticker.get()));
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
    if(_currentTime >= _timeToTick)
    {
        //at least one it should be
        int numberOfTicks = floor(_currentTime/_timeToTick);
        assert(numberOfTicks >= 1);

        _currentTime = 0;
        for(int i = 0; i < numberOfTicks; i++)
        {
            if(_currentIndex >= _data.size()) {
                _simulating = false;
                return;
            }

            auto& tickData = _data[_currentIndex++];
            _ticker->tick(tickData);
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

std::shared_ptr<Indicator> BackTestingContext::loadIndicator(IndicatorsView::CandleIndicatorsTypes type, bool shouldCreateNode) {

    if(_ticker == nullptr)
        return nullptr;

    std::shared_ptr<Indicator> indicator{nullptr};

    switch (type) {
        case IndicatorsView::CandleIndicatorsTypes::SMA: {
            std::shared_ptr<SMA> sma = std::make_unique<SMA>(_ticker.get());
            sma->setPriority(1);
            _indicators.push_back(std::move(sma));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::SMA,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::BOLL: {
            std::shared_ptr<Bollinger> boll = std::make_shared<Bollinger>(_ticker.get());
            boll->setPriority(1);
            _indicators.push_back(std::move(boll));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::EMA: {
            std::shared_ptr<EMA> ema = std::make_shared<EMA>(_ticker.get());
            ema->setPriority(1);
            _indicators.push_back(std::move(ema));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::WMA: {

            std::shared_ptr<WMA> wma = std::make_shared<WMA>(_ticker.get());
            _indicators.push_back(std::move(wma));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::AVL:
        case IndicatorsView::CandleIndicatorsTypes::VWAP:
        case IndicatorsView::CandleIndicatorsTypes::TRIX:
        {
            std::shared_ptr<TRIX> trix = std::make_shared<TRIX>(_ticker.get());
            _subplotIndicators.push_back(std::move(trix));
            indicator = _subplotIndicators.back();
            _ticker->addTickable(_subplotIndicators.back().get());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::PSAR :
        {
            std::shared_ptr<PSAR> psar = std::make_shared<PSAR>(_ticker.get());
            _indicators.push_back(std::move(psar));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
        }
            break;
        default:
            break;
    }

    return indicator;
}

void BackTestingContext::plotIndicators() {
    for(auto& i : _indicators) {
        i->render();
        if (ImPlot::BeginDragDropSourceItem(i->getPlotName().c_str())) {
            ImGui::SetDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID_REMOVING, &i, sizeof(std::shared_ptr<Indicator>));
            ImPlot::EndDragDropSource();
        }
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
    if(_strategy)
        _strategy->render();
}

//develop phase
void BackTestingContext::showTabBars(bool show) {
    for(auto& w : getWidgets()){
        w->showTabBar(show);
    }
    MainMenuBar::_show_tabbars = show;
}

std::shared_ptr<INode> BackTestingContext::createIndicatorNode(UiNodeType type, std::shared_ptr<Indicator> indicator)
{
    std::shared_ptr<INode> node{nullptr};

    switch (type) {
        case UiNodeType::SMA:
        {
                node = std::make_shared<SMANode>(indicator,_strategyEditor);
                _strategyEditor->addNode(node);
            }
            break;
        default:
            break;
    }

    return node;
}

//this will be called from strategy editor widget
std::shared_ptr<INode> BackTestingContext::createNode(std::shared_ptr<graph::Graph<GraphNode>> _graph, UiNodeType type)
{
    std::shared_ptr<INode> node{nullptr};

    switch (type) {
        case UiNodeType::SMA:
            node = std::make_shared<SMANode>(loadIndicator(IndicatorsView::CandleIndicatorsTypes::SMA, true),_strategyEditor);
            break;
        case UiNodeType::CROSS:
            node = std::make_shared<CrossNode>(_strategyEditor);
            break;
        case UiNodeType::COUNTER:
            {
                node = std::make_shared<Counter>(_strategyEditor);
                getWidget<StrategyEditor>()->addRootId(node->getId());
            }
            break;
        case UiNodeType::TRADE:
            {
                //if already has an active strategy change it
                if(_strategy != nullptr)
                {
                    _ticker->removeTickable(_strategy.get());
                    _strategy.reset();
                }

                _strategy = std::make_shared<TradeNodeStrategy>(_ticker.get());
                auto strategyPtr = dynamic_cast<TradeNodeStrategy *>(_strategy.get());

                strategyPtr->setPriority(3);
                _ticker->addTickable(strategyPtr);

                getWidget<ProfitAndLossesView>()->setStrategyTest(_strategy);
                node = std::make_shared<TradeNode>(_strategyEditor,strategyPtr);
                _strategyEditor->addRootId(node->getId());
             }
            break;
        case UiNodeType::BAR_SEQ_UP:
            node = std::make_shared<UpSequenceNode>(_strategyEditor,_ticker.get());
            break;
        case UiNodeType::BAR_SEQ_DOWN:
            node = std::make_shared<DownSequenceNode>(_strategyEditor,_ticker.get());
            break;
            //TEMP TEST
        case UiNodeType::TREND:
            node = std::make_shared<BarValueNode>(_strategyEditor,_ticker.get());
            break;
        default:
            break;
    }

    return node;
}

void BackTestingContext::removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) {

    //first delete from ticker
    if(_ticker->removeTickable(indicator.get()))
        puts("indicator removed successfully");

    //now delete from indicators list
    for(auto it = _indicators.begin(); it != _indicators.end(); it++){
        if((*it)->getId() == indicator->getId())
        {
            if (shouldDeleteNode)
                getWidget<StrategyEditor>()->removeNodeIndicator(indicator);

            _indicators.erase(it);
            break;
        }
    }

    //now delete from indicators list
    for(auto it = _subplotIndicators.begin(); it != _subplotIndicators.end(); it++){
        if((*it)->getId() == indicator->getId())
        {
            if (shouldDeleteNode)
                getWidget<StrategyEditor>()->removeNodeIndicator(indicator);

            _subplotIndicators.erase(it);
            break;
        }
    }
}

void BackTestingContext::removeAllIndicators() {
    auto strategyEditor = getWidget<StrategyEditor>();
    for(auto& i : _indicators){
        strategyEditor->removeNodeIndicator(i);
        if(_ticker->removeTickable(i.get()))
            puts("indicator removed successfully");
    }

    for(auto& i : _subplotIndicators){
        strategyEditor->removeNodeIndicator(i);
        if(_ticker->removeTickable(i.get()))
            puts("indicator removed successfully");
    }

    _indicators.clear();
    _subplotIndicators.clear();
}

void BackTestingContext::plotSubplotIndicators() {
    for(auto& i : _subplotIndicators) {
        if (ImPlot::BeginPlot(("##"+i->getPlotName()).c_str())) {
            i->render();
            if (ImPlot::BeginDragDropSourceItem(i->getPlotName().c_str())) {
                ImGui::SetDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID_REMOVING, &i, sizeof(std::shared_ptr<Indicator>));
                ImPlot::EndDragDropSource();
            }
            ImPlot::EndPlot();
        }
    }
}





