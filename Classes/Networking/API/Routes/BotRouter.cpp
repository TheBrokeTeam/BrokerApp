//
// Created by Maykon Meneghel on 26/04/22.
//

#include "BotRouter.h"
#include "../../../Common/Json/BAJson.h"

BotRouter::BotRouter() = default;

APIRouter BotRouter::save(const rapidjson::Document &body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    apiRouter.setBody(BAJson::stringfy(body));
    return apiRouter;
}

APIRouter BotRouter::fetchByUserId(const std::string& userId) const {
    return { get, this->endpoint + "?userId=" + userId };
}

APIRouter BotRouter::deleteById(const std::string& id) const {
    APIRouter apiRouter = APIRouter(del, this->endpoint);
    return {del, this->endpoint + "?id=" + id }  ;
}