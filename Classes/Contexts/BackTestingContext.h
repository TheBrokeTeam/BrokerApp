//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BACKTESTINGCONTEXT_H
#define BROKERAPP_BACKTESTINGCONTEXT_H

#include "Context.h"
#include <map>
#include <set>

class BackTestingContext : public Context {
public:
    struct DownloadResponse {
        bool success{false};
        std::string extractedFileName{""};
    };

    BackTestingContext() = default;

    Ticker* loadSymbol(const Symbol &symbol) override;
    void loadTicker(const Symbol& symbol) override;
    void update(float dt) override;

    void startSimulation(Ticker* ticker) override;
    void setSimulationSpeed(float speed) override;
    bool isSimulating() override;

private:

    bool dataAlreadyExists(const Symbol& symbol);
    std::vector<TickData> loadCsv(const Symbol& symbol);
    std::string getFilePathFromSymbol(const Symbol& symbol);

    std::string build_url(std::string symbol, std::string year, std::string month, std::string interval);

    DownloadResponse download_file(std::string url, std::string filename);

    std::map<Symbol,Ticker> _tickers;
    std::map<std::string,std::vector<TickData>> _data;

    //simulating
    Ticker* _tickerToSimulate{nullptr};
    int _countTicks = 0;
    bool _simulating = false;
    int _currentIndex = 0;
    float _timeToTick = 0.5f; //sec
    float _currentTime = 0;
    float _speed = 1.0f;
    float _speedLimit = 1000.0f;


};

#endif //BROKERAPP_BACKTESTINGCONTEXT_H
