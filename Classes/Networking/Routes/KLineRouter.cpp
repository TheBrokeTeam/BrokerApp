//
// Created by Maykon Meneghel on 23/01/22.
//

#include "KLineRouter.h"

KLineRouter::KLineRouter() = default;

APIRouter KLineRouter::getData(Symbol symbol) const {
    return {get, this->endpoint + "?symbol=" + symbol.getName() +  "&interval=" + symbol.getInterval() + "&startTime=" +  std::to_string(symbol.getStartTime()) + "&endTime=" + std::to_string(symbol.getEndTime()) + "&limit=" + std::to_string(1000)};
}