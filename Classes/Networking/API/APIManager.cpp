//
// Created by Maykon Meneghel on 07/01/22.
//

#include "APIManager.h"
#include "APIRouter.h"

APIManager::APIManager() = default;

rapidjson::Document APIManager::Request(APIRouter router) {
    return router.request(this->serverURL);
}

void APIManager::Download(APIRouter router, Symbol::Path path) {
    return router.download(this->csvURL, path);
}

std::string APIManager::getURL() {
    return this->serverURL;
}
