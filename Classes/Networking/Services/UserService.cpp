//
// Created by Maykon Meneghel on 10/01/22.
//

#include <map>
#include <utility>
#include "UserService.h"
#include "../Routes/UserRouter.h"

UserService::UserService() = default;

Json::Value UserService::createNewUser(Json::Value body) {
    return this->apiManager.Request(UserRouter().createOne(std::move(body)));
}

Json::Value UserService::deleteUser() {
    return this->apiManager.Request(UserRouter().deleteOne());
}

Json::Value UserService::getAccessKey(Json::Value body) {
    return this->apiManager.Request(UserRouter().getAuthorization(std::move(body)));
}

Json::Value UserService::updateUser() {
    return this->apiManager.Request(UserRouter().updateOne());
}