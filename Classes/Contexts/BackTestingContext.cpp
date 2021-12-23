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


void BackTestingContext::loadSymbol(const Symbol& symbol) {
    Context::loadSymbol(symbol);

    puts("TODO load symbol!");

    std::string filename = "data.zip";

    static const std::string interval_str[]{"1m", "3m", "5m", "15m", "30m", "1h",
                                            "2h", "4h", "6h", "8h", "12h", "1d",
                                            "3d", "1w", "1mo"};

    auto url = build_url(symbol.getName(),"2021","01",interval_str[int(symbol.getTimeInterval())]);
    auto resp = download_file(url,filename);
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



