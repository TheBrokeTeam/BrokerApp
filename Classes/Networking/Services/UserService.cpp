//
// Created by Maykon Meneghel on 10/01/22.
//

#include "UserService.h"
#include "../Routes/UserRouter.h"
#include <fmt/format.h>

UserService::UserService() = default;

//rapidjson::Document UserService::createNewUser() {
//    return this->apiManager.Request(UserRouter().createOne());
//}

rapidjson::Document UserService::authenticate(const rapidjson::Document& body) {
    return this->apiManager.Request(UserRouter().authenticate(body));
}

//rapidjson::Document UserService::getGitHubToken() {
//    return this->apiManager.Request(UserRouter().getGitHubAuthorization());
//}

rapidjson::Document UserService::deleteUser() {
    return this->apiManager.Request(UserRouter().deleteOne());
}

rapidjson::Document UserService::updateUser() {
    return this->apiManager.Request(UserRouter().updateOne());
}

void UserService::openAuth(const std::string& provider){
    this->openPlatform(this->apiManager.getURL() + fmt::format("/users/auth?provider={}", provider));
}

void UserService::openPlatform(const std::string& url)
{
    std::string str;
    switch (platform) {
        case 1:
            str = "explorer";
            break;
        case 2:
            str = "xdg-open";
            break;
        case 3:
            str = "open";
            break;
        default:
            std::cout << "Should never happen on the 3 defined platforms" << std::endl;
    }
    str.append(" " + url);
    std::system(str.data());
}
