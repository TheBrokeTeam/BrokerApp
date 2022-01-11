//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIMANAGER_H
#define UNTITLED1_APIMANAGER_H

#include "APIRouter.h"
#include <string>

class APIManager {
protected:
    std::string baseURL = "http://localhost:3200";
    std::string accessKey = "XXX";
public:
    APIManager();
    Json::Value Request(APIRouter router);
};

#endif //UNTITLED1_APIMANAGER_H
