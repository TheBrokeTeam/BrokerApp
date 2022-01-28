//
// Created by Maykon Meneghel on 23/01/22.
//

#include "KLineService.h"
#include "../Routes/KLineRouter.h"

KLineService::KLineService() = default;

rapidjson::Document KLineService::fetchData(const std::string& symbol, const std::string& interval, long startTime, long endTime, int limit) {
    return this->apiManager.Request(KLineRouter().getData(symbol, interval, startTime, endTime, limit));
}

void KLineService::downloadData(const std::string& symbol, const std::string& interval, const std::string& date, Symbol::Path path) {
    return this->apiManager.Download(KLineRouter().getCSVData(symbol, interval, date), path);
}
