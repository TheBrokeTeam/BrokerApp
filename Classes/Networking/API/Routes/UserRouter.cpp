//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserRouter.h"
//#include "../../../Helpers/JsonUtils.h"
#include "../../../Common/Json/BAJson.h"

UserRouter::UserRouter() = default;

APIRouter UserRouter::createOne() const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    return apiRouter;
}

APIRouter UserRouter::authenticate(const rapidjson::Document& body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint + "/auth");
    apiRouter.setBody(BAJson::stringfy(body));
    std::cout << BAJson::stringfy(body) << std::endl;
    return apiRouter;
}

APIRouter UserRouter::deleteOne() const {
    return {del, this->endpoint};
}

APIRouter UserRouter::getName(const std::string & id) const {
    return {get, this->endpoint + "/" + id + "?scope=name"};
}

APIRouter UserRouter::logout() const {
    APIRouter apiRouter = APIRouter(get, "/logout");
//    apiRouter.setBody(BAJson::stringfy(body));
    return apiRouter;
}
