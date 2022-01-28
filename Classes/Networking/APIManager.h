//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_APIMANAGER_H
#define UNTITLED1_APIMANAGER_H

#include "APIRouter.h"
#include <string>

class APIManager {
protected:
    std::string baseURL = "https://api.binance.com/api/v3";
    std::string csvURL = "https://data.binance.vision/data/spot/monthly";
    std::string accessKey = "XXX";
public:
    APIManager();
    rapidjson::Document Request(APIRouter);
    rapidcsv::Document Download(APIRouter, const std::string&);

};

#endif //UNTITLED1_APIMANAGER_H
