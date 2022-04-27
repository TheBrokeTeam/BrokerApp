//
// Created by Maykon Meneghel on 26/04/22.
//

#include "BotService.h"
#include "../Routes/BotRouter.h"

BotService::BotService() = default;

rapidjson::Document BotService::saveBot(const rapidjson::Document& strategy) {
    return this->apiManager.Request(BotRouter().save(strategy));
}

rapidjson::Document BotService::deleteBot(const std::string& id) {
    return this->apiManager.Request(BotRouter().deleteById(id));
}

rapidjson::Document BotService::fetchBots(const std::string& userId) {
    return this->apiManager.Request(BotRouter().fetchByUserId(userId));
}
