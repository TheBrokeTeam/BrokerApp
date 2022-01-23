//
// Created by Maykon Meneghel on 23/01/22.
//

#include "KLineService.h"
#include "../Routes/KLineRouter.h"

KLineService::KLineService() = default;

rapidjson::Document KLineService::fetchData(const Symbol& symbol) {
    return this->apiManager.Request(KLineRouter().getData(symbol));
}