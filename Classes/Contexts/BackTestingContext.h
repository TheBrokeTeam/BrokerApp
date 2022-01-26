//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BACKTESTINGCONTEXT_H
#define BROKERAPP_BACKTESTINGCONTEXT_H

#include "Context.h"
#include <map>
#include <set>
#include <rapidjson/document.h>

class BackTestingContext : public Context {
public:
    struct DownloadResponse {
        bool success{false};
        std::string extractedFileName{""};
    };

    BackTestingContext(Editor* editor);
    void initialize() override;

    Ticker* fetchDataSymbol(Symbol symbol) override;
//    void loadSymbol(Symbol symbol) override;
    void loadTicker() override;
    void updateData(float dt) override;

    void startSimulation(Ticker* ticker) override;
    void setSimulationSpeed(float speed) override;
    bool isSimulating() override;

    std::shared_ptr<Indicator> loadIndicator(IndicatorsView::CandleIndicatorsTypes type,bool shouldCreateNode = false) override;
    std::shared_ptr<INode> createIndicatorNode(UiNodeType type, std::shared_ptr<Indicator> indicator) override;
    std::shared_ptr<INode> createNode(std::shared_ptr<graph::Graph<GraphNode>> _graph, UiNodeType type) override;


    void removeIndicator(std::shared_ptr<Indicator> indicator,bool shouldDeleteNode) override;
    void removeAllIndicators() override;


    void plotIndicators() override;
    void plotSubplotIndicators() override;

    void plotStrategy() override;

    void showTabBars(bool show) override;

private:

//    bool dataAlreadyExists(const Symbol& symbol);

//    std::vector<TickData> loadCsv(Symbol symbol);

//    std::string getSymbolFilePath(Symbol symbol);

//    std::string build_url(std::string symbol, std::string year, std::string month, std::string interval);

//    DownloadResponse download_file(std::string url, std::string filename);

    //TODO:: single symbol for now until backtesting is good
    std::shared_ptr<Ticker> _ticker{nullptr};
    std::shared_ptr<Strategy> _strategy{nullptr};
    StrategyEditor* _strategyEditor{nullptr};


    std::vector<TickData> _data;

    //simulating
    int _countTicks = 0;
    bool _simulating = false;
    int _currentIndex = 0;
    float _timeToTick = 0.5f; //sec
    float _currentTime = 0;
    float _speed = 1.0f;
    float _speedLimit = 1000.0f;

    //joke time
    bool _shouldShowLuizPopup = false;
};

#endif //BROKERAPP_BACKTESTINGCONTEXT_H
