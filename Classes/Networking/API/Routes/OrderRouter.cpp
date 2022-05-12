//
// Created by Maykon Meneghel on 12/05/22.
//

#include "OrderRouter.h"
#include "../../../Common/Json/BAJson.h"

OrderRouter::OrderRouter() = default;

APIRouter OrderRouter::createOrder(const rapidjson::Document &body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    apiRouter.setBody(BAJson::stringfy(body));
    return apiRouter;
}

APIRouter OrderRouter::fetchByUserId(const std::string& userId) const {
    return { get, this->endpoint + "?userId=" + userId };
}

APIRouter OrderRouter::deleteById(const std::string& id) const {
    APIRouter apiRouter = APIRouter(del, this->endpoint);
    return {del, this->endpoint + "?id=" + id }  ;
}