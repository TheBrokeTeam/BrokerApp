//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserRouter.h"
#include "../../../Helpers/JsonUtils.h"

UserRouter::UserRouter() = default;

APIRouter UserRouter::createOne() const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    return apiRouter;
}

APIRouter UserRouter::authenticate(const rapidjson::Document& body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint + "/auth");
    apiRouter.setBody(json::Stringfy(body));
    std::cout << json::Stringfy(body) << std::endl;
    return apiRouter;
}

APIRouter UserRouter::updateOne() const {
    return {patch, this->endpoint};
}

APIRouter UserRouter::deleteOne() const {
    return {del, this->endpoint};
}

APIRouter UserRouter::getGitHubAuthorization() const {
    APIRouter apiRouter = APIRouter(post, this->endpoint + "/auth/github");
    return apiRouter;
}
