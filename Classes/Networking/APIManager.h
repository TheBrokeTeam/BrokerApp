//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIMANAGER_H
#define UNTITLED1_APIMANAGER_H

#include "APIRouter.h"
#include <string>

class APIManager {
protected:
    std::string baseURL = "https://preditchart.com.br";
    std::string accessKey = "XXX";
public:
    APIManager();
    rapidjson::Document Request(APIRouter router);
};

#endif //UNTITLED1_APIMANAGER_H
