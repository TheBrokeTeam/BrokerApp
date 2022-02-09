//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserRouter.h"
#include "../../../Helpers/JsonUtils.h"

UserRouter::UserRouter() = default;

APIRouter UserRouter::createOne(const rapidjson::Document& body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    apiRouter.setBody(json::Stringfy(body));
    return apiRouter;
}

APIRouter UserRouter::getAuthorization(const rapidjson::Document& body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint + "/auth");
    apiRouter.setBody(json::Stringfy(body));
    return apiRouter;
}

APIRouter UserRouter::updateOne() const {
    return {patch, this->endpoint};
}

APIRouter UserRouter::deleteOne() const {
    return {del, this->endpoint};
}
