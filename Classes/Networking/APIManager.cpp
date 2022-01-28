//
// Created by Maykon Meneghel on 07/01/22.
//

#include "APIManager.h"
#include "APIRouter.h"

APIManager::APIManager() = default;

rapidjson::Document APIManager::Request(APIRouter router) {
    return router.request(this->baseURL);
}

rapidcsv::Document APIManager::Download(APIRouter router, const std::string& filename) {
    return router.download(this->csvURL, filename);
}
