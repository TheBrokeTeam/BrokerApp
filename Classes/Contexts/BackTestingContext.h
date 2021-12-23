//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BACKTESTINGCONTEXT_H
#define BROKERAPP_BACKTESTINGCONTEXT_H


#include "Context.h"
#include <map>
#include <set>
#include "../Tickers/Ticker.h"

class BackTestingContext : public Context {
public:
    struct DownloadResponse {
        bool success{false};
        std::string extractedFileName{""};
    };

    BackTestingContext() = default;

    void loadSymbol(const Symbol &symbol) override;

private:
    void loadTicker(const Symbol& symbol);

    bool dataAlreadyExists(const Symbol& symbol);
    void fillData(const Symbol& symbol);
    std::vector<TickData> loadCsv(const Symbol& symbol);
    std::string getFilePathFromSymbol(const Symbol& symbol);

    std::string build_url(std::string symbol, std::string year, std::string month, std::string interval);

    DownloadResponse download_file(std::string url, std::string filename);

    std::map<Symbol,Ticker> _tickers;
    std::map<std::string,std::vector<TickData>> _data;

};

#endif //BROKERAPP_BACKTESTINGCONTEXT_H
