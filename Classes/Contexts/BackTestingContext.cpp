//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#include "BackTestingContext.h"

#include <curl/curl.h>
#include "../Tickables/Indicators/SMA.h"
#include "../Tickables/Indicators/Bollinger.h"
#include "../Tickables/Indicators/EMA.h"
#include "../Tickables/Indicators/TRIX.h"
#include "../Tickables/Indicators/WMA.h"
#include "../Tickables/Indicators/PSAR.h"
#include "../Tickables/Indicators/MFI.h"
#include "../Tickables/Indicators/VWAP.h"
#include "../Widgets/MainMenuBar.h"
#include "../Widgets/DownloaderView.h"
#include "../Widgets/SimulationController.h"
#include "../Widgets/ProfitAndLossesView.h"
#include "../Widgets/ChartView.h"
#include "../Widgets/StrategyEditor.h"
#include "../Widgets/StockList.h"
#include "../Nodes/SMANode.h"
#include "../Nodes/PSARNode.h"
#include "../Nodes/BollingerNode.h"
#include "../Nodes/CrossNode.h"
#include "../Nodes/Counter.h"
#include "../Nodes/TradeNode.h"
#include "../Nodes/UpSequenceNode.h"
#include "../Nodes/DownSequenceNode.h"
#include "../Nodes/BarValueNode.h"
#include "../Nodes/VWAPNode.h"
#include "../Nodes/EMANode.h"
#include "../Nodes/WMANode.h"
#include "../Nodes/TRIXNode.h"

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
    });

    _strategyEditor->setPriority(2);
    _ticker->addTickable(_strategyEditor);
}

//void BackTestingContext::loadSymbol(Symbol symbol) {
//
//    std::string filename = "data.zip";
//    auto url = build_url(symbol.getCode(),symbol.year,symbol.month,symbol.getInterval());
//
//    if(!dataAlreadyExists(symbol))
//        auto resp = download_file(url,filename);
//
//    _data.clear();
//    _data = loadCsv(symbol);
//
//    _ticker->setSymbol(symbol);
//    _ticker->reset();
//    loadTicker();
//
//    auto chart = getWidget<ChartView>();
//    chart->addChart(std::make_shared<CandleChart>(this,_ticker.get()));
//}

//BackTestingContext::DownloadResponse BackTestingContext::download_file(std::string url, std::string filename) {
//    bool success = false;
//    CURL *curl;
//    FILE *fp;
//    CURLcode res;
//    curl = curl_easy_init();
//    DownloadResponse response;
//    if (curl) {
//        fp = fopen(filename.c_str(), "wb");
//        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
//
//        //TODO:: I dont know if this is ok based on these comments:
//        //https://stackoverflow.com/questions/25540547/how-to-download-a-zip-file-from-server-using-curl-in-c
//
//        curl_easy_setopt(curl, CURLOPT_CAINFO, "./ca-bundle.crt");
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
//        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);
//        //###########################################################
//
//        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
//        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
//        res = curl_easy_perform(curl);
//        if (res == 0)
//            success = true;
//        curl_easy_cleanup(curl);
//        fclose(fp);
//
//        response.success = success;
//
//        if(!response.success)
//            return response;
//
////        //TODO::remove the unzip from here
////        miniz_cpp::zip_file file(filename);
////        file.extractall("./");
////
////        namespace fs = std::filesystem;
////
////        fs::remove(filename);
////
////        response.extractedFileName = file.getinfo(0).filename;
//    }
//    return response;
//}

//// TODO:
//std::string BackTestingContext::build_url(std::string symbol, std::string year, std::string month, std::string interval) {
//
//    return fmt::format("https://data.binance.vision/data/spot/monthly/klines/{}/{}/{}-{}-{}-{}.zip",
//                       symbol,
//                       interval,
//                       symbol,
//                       interval,
//                       year,
//                       month
//    );
//}

//// TODO:
//bool BackTestingContext::dataAlreadyExists(const Symbol &symbol) {
//    return std::filesystem::exists(getSymbolFilePath(symbol));
//}

bool BackTestingContext::isSimulating() {
    return _simulating;
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
    getWidget<ProfitAndLossesView>()->clear();
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
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::BOLL,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::EMA: {
            std::shared_ptr<EMA> ema = std::make_shared<EMA>(_ticker.get());
            ema->setPriority(1);
            _indicators.push_back(std::move(ema));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::EMA,_indicators.back());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::WMA: {

            std::shared_ptr<WMA> wma = std::make_shared<WMA>(_ticker.get());
            wma->setPriority(1);
            _indicators.push_back(std::move(wma));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::WMA,_indicators.back());
        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::VWAP: {
            std::shared_ptr<VWAP> vwap = std::make_shared<VWAP>(_ticker.get());
            vwap->setPriority(1);
            _indicators.push_back(std::move(vwap));
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::VWAP,_indicators.back());

        }
            break;

        case IndicatorsView::CandleIndicatorsTypes::TRIX:
        {
            std::shared_ptr<TRIX> trix = std::make_shared<TRIX>(_ticker.get());
            trix->setPriority(1);
            _subplotIndicators.push_back(std::move(trix));
            indicator = _subplotIndicators.back();
            _ticker->addTickable(_subplotIndicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::TRIX,_subplotIndicators.back());

        }
            break;
        case IndicatorsView::CandleIndicatorsTypes::PSAR :
        {
            std::shared_ptr<PSAR> psar = std::make_shared<PSAR>(_ticker.get());
            psar->setPriority(1);
            _indicators.push_back(std::move(psar));
            indicator = _indicators.back();
            _ticker->addTickable(_indicators.back().get());
            if(shouldCreateNode)
                createIndicatorNode(UiNodeType::PSAR,_indicators.back());

        }
        break;
        case IndicatorsView::CandleIndicatorsTypes::MFI :
        {
            std::shared_ptr<MFI> mfi = std::make_shared<MFI>(_ticker.get());
            mfi->setPriority(1);
            _subplotIndicators.push_back(std::move(mfi));
            indicator = _subplotIndicators.back();
            _ticker->addTickable(_subplotIndicators.back().get());
            //if(shouldCreateNode)
              //  createIndicatorNode(UiNodeType::MFI,_indicators.back());
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
    Editor::show_tabbars = show;
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
        case UiNodeType::EMA:
        {
            node = std::make_shared<EMANode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
        case UiNodeType::WMA:
        {
            node = std::make_shared<WMANode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
        case UiNodeType::BOLL:
        {
            node = std::make_shared<BollingerNode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
        case UiNodeType::PSAR:
        {
            node = std::make_shared<PSARNode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
        case UiNodeType::VWAP:
        {
            node = std::make_shared<VWAPNode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
        case UiNodeType::TRIX:
        {
            node = std::make_shared<TRIXNode>(indicator,_strategyEditor);
            _strategyEditor->addNode(node);
        }
        break;
//        case UiNodeType::MFI:
//        {
//            node = std::make_shared<MFINode>(indicator,_strategyEditor);
//            _strategyEditor->addNode(node);
//        }
//            break;
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
        case UiNodeType::BOLL:
            node = std::make_shared<BollingerNode>(loadIndicator(IndicatorsView::CandleIndicatorsTypes::BOLL, true),_strategyEditor);
            break;
        case UiNodeType::VWAP:
            node = std::make_shared<VWAPNode>(loadIndicator(IndicatorsView::CandleIndicatorsTypes::VWAP, true),_strategyEditor);
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

                _strategy->setClosePositionCallback([this](const Strategy::Position& position){
                   getWidget<ProfitAndLossesView>()->onClosePosition(position);
                });
                getWidget<ProfitAndLossesView>()->setStrategyTest(_strategy);

                auto strategyPtr = dynamic_cast<TradeNodeStrategy *>(_strategy.get());

                strategyPtr->setPriority(3);
                _ticker->addTickable(strategyPtr);

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
            i->render();
    }
}

void BackTestingContext::handleDragDrop(PlotItem *plotItem) {
    std::shared_ptr<Indicator> ind{nullptr};

    for(auto& i : _subplotIndicators) {
        if (i.get() == plotItem) {
            ind = i;
        }
    }

    for(auto& i : _indicators) {
        if (i.get() == plotItem) {
            ind = i;
        }
    }

    if (ind != nullptr) {
        if (ImPlot::BeginDragDropSourceItem(ind->getPlotName().c_str())) {
            ImGui::SetDragDropPayload(IndicatorsView::CANDLE_INDICATORS_DRAG_ID_REMOVING, &ind,
                                      sizeof(std::shared_ptr<Indicator>));
            ImPlot::EndDragDropSource();
        }
    }

}

Ticker *BackTestingContext::fetchDataSymbol(Symbol symbol) {
    _ticker->reset();
    _ticker->setSymbol(symbol);

    _data.clear();

    _data = symbol.fetchCSVData();

//    _data = symbol.fetchData();
    loadTicker();

    setShouldRender(true);
    auto chart = getWidget<ChartView>();
    chart->addChart(std::make_shared<CandleChart>(this,_ticker.get()));


    return _ticker.get();
}

void BackTestingContext::openSymbolStream() {
    _socket_manager.openStream();
}

void BackTestingContext::closeSymbolStream() {
    _socket_manager.closeStream();
}
