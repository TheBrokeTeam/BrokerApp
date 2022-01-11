//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserRouter.h"

#include <utility>
#include <iostream>

UserRouter::UserRouter() = default;

APIRouter UserRouter::createOne(Json::Value body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint);
    apiRouter.setBody(std::move(body));
    return apiRouter;
}

APIRouter UserRouter::getAuthorization(Json::Value body) const {
    APIRouter apiRouter = APIRouter(post, this->endpoint + "/auth");
    apiRouter.setBody(std::move(body));
    return apiRouter;
}

APIRouter UserRouter::updateOne() const {
    return {patch, this->endpoint};
}

APIRouter UserRouter::deleteOne() const {
    return {del, this->endpoint};
}
