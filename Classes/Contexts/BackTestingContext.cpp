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

static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                        "2h", "4h", "6h", "8h", "12h", "1d",
                                        "3d", "1w", "1mo"};

Ticker* BackTestingContext::loadSymbol(const Symbol& symbol) {
    puts("TODO load symbol!");

    std::string filename = "data.zip";

    auto url = build_url(symbol.getName(),"2021","01",interval_str[int(symbol.getTimeInterval())]);

    if(!dataAlreadyExists(symbol))
        auto resp = download_file(url,filename);

    //create a ticker for the symbol loaded
    auto ticker = Ticker(this,std::make_shared<Symbol>(symbol));
    _tickers.emplace(symbol,ticker);

    //load tickdata from symbol file already donwloaded
    _data.emplace(symbol.getName(),loadCsv(symbol));

    return &_tickers.at(symbol);

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
        data_open.time  = doc.GetCell<long>(0,i)/1000.0;
        data_high.time  = doc.GetCell<long>(0,i)/1000.0 + symbol.getTimeIntervalInMinutes()*0.25 * 60;
        data_low.time  = doc.GetCell<long>(0,i)/1000.0 + symbol.getTimeIntervalInMinutes()*0.5* 60;
        data_close.time  = doc.GetCell<long>(0,i)/1000.0 + symbol.getTimeIntervalInMinutes()*60 - 1;

        data_open.price = doc.GetCell<double>(1,i);
        data_high.price = doc.GetCell<double>(2,i);
        data_low.price = doc.GetCell<double>(3,i);
        data_close.price = doc.GetCell<double>(4,i);

        data_open.volume = doc.GetCell<double>(5,i)*0.25;
        data_high.volume = doc.GetCell<double>(5,i)*0.5;
        data_low.volume = doc.GetCell<double>(5,i)*0.75;
        data_close.volume = doc.GetCell<double>(5,i);

        output.push_back(data_open);
        output.push_back(data_high);
        output.push_back(data_low);
        output.push_back(data_close);
    }

    return output;
}

std::string BackTestingContext::getFilePathFromSymbol(const Symbol& symbol) {

    std::string out = fmt::format("./{}-{}-{}-{}.csv",
            symbol.getName(),
            interval_str[int(symbol.getTimeInterval())],
            "2021",
            "01");

    return out;
}

void BackTestingContext::loadTicker(const Symbol &symbol) {
    auto& ticker = _tickers.at(symbol);
    auto& vec = _data.at(symbol.getName());
    for(auto& d : vec)
        ticker.tick(d);
}



