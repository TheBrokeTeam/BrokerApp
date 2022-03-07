//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIMANAGER_H
#define UNTITLED1_APIMANAGER_H

#include "APIRouter.h"
#include "../Data/Symbol.h"
#include <string>

class APIManager {
protected:
    std::string baseURL = "https://api.binance.com/api/v3";
    std::string serverURL = "http:/localhost:3200";
    std::string csvURL = "https://data.binance.vision/data/spot/monthly";
    std::string accessKey = "XXX";
public:
    APIManager();
    rapidjson::Document Request(APIRouter);
    void Download(APIRouter, Symbol::Path);
    std::string getURL();

};

#endif //UNTITLED1_APIMANAGER_H
