//
// Created by Maykon Meneghel on 23/01/22.
//

#include "KLineRouter.h"

KLineRouter::KLineRouter() = default;

APIRouter KLineRouter::getData(const std::string& symbol, const std::string& interval, long startTime, long endTime, int limit) const {
    return {get, this->endpoint + "?symbol=" + symbol +  "&interval=" + interval + "&startTime=" +  std::to_string(startTime) + "&endTime=" + std::to_string(endTime) + "&limit=" + std::to_string(limit)};
}

APIRouter KLineRouter::getCSVData(const std::string& symbol, const std::string& interval, const std::string& date) const {
    return {get, this->endpoint + "/" + symbol +  "/" + interval + "/" +  symbol + "-" + interval + "-" + date + ".zip"};
}