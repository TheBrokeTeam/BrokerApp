//
// Created by Maykon Meneghel on 26/04/22.
//

#include "StrategyService.h"
#include "../Routes/StrategyRouter.h"

StrategyService::StrategyService() = default;

rapidjson::Document StrategyService::saveStrategy(const rapidjson::Document& strategy) {
    return this->apiManager.Request(StrategyRouter().save(strategy));
}

rapidjson::Document StrategyService::deleteStrategy(const std::string& id) {
    return this->apiManager.Request(StrategyRouter().deleteById(id));
}

rapidjson::Document StrategyService::fetchStrategies(const std::string& userId) {
    return this->apiManager.Request(StrategyRouter().fetchByUserId(userId));
}
