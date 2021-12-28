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


private:

    bool dataAlreadyExists(const Symbol& symbol);
    std::vector<TickData> loadCsv(const Symbol& symbol);
    std::string getFilePathFromSymbol(const Symbol& symbol);

    std::string build_url(std::string symbol, std::string year, std::string month, std::string interval);

    DownloadResponse download_file(std::string url, std::string filename);

    std::map<Symbol,Ticker> _tickers;
    std::map<std::string,std::vector<TickData>> _data;
    std::vector<double> _time;
    int _end_Idx;
    int _start_Idx;

    bool shouldUpdateTicker = false;

};

#endif //BROKERAPP_BACKTESTINGCONTEXT_H
