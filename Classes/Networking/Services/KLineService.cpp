//
// Created by Maykon Meneghel on 23/01/22.
//

#include "KLineService.h"
#include "../Routes/KLineRouter.h"

KLineService::KLineService() = default;

rapidjson::Document KLineService::fetchData(const std::string& symbol, const std::string& interval, long startTime, long endTime, int limit) {
    return this->apiManager.Request(KLineRouter().getData(symbol, interval, startTime, endTime, limit));
}

rapidcsv::Document KLineService::fetchCSVData(const std::string& symbol, const std::string& interval, const std::string& date, const std::string& filename) {
    return this->apiManager.Download(KLineRouter().getCSVData(symbol, interval, date), filename);
}
