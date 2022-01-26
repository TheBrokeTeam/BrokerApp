//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserService.h"
#include "../Routes/UserRouter.h"

UserService::UserService() = default;

rapidjson::Document UserService::createNewUser(const rapidjson::Document& body) {
    return this->apiManager.Request(UserRouter().createOne(body));
}

rapidjson::Document UserService::getAccessKey(const rapidjson::Document& body) {
    return this->apiManager.Request(UserRouter().getAuthorization(body));
}

rapidjson::Document UserService::deleteUser() {
    return this->apiManager.Request(UserRouter().deleteOne());
}

rapidjson::Document UserService::updateUser() {
    return this->apiManager.Request(UserRouter().updateOne());
}