//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_BACKTESTINGCONTEXT_H
#define BROKERAPP_BACKTESTINGCONTEXT_H


#include "Context.h"

class BackTestingContext : public Context {
public:
    struct DownloadResponse {
        bool success{false};
        std::string extractedFileName{""};
    };

    BackTestingContext() = default;

    void loadSymbol(const Symbol &symbol) override;

    std::string build_url(std::string symbol, std::string year, std::string month, std::string interval);

    DownloadResponse download_file(std::string url, std::string filename);

};

#endif //BROKERAPP_BACKTESTINGCONTEXT_H
