//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#include "DBManager.h"
#include "Paths.h"
#include "../Json/BAJson.h"

DBManager::DBManager() {
    loadKeys();
}

DBManager::~DBManager() {

}

const AccountInfo&  DBManager::loadUserData() {
    //load the info on _userAccountInfo
    return _userAccountInfo;
}

void DBManager::updateUserData(const AccountInfo &info) {
    //update info on _userAccountInfo except hor
    _userAccountInfo.update(info);
}

void DBManager::loadKeys() {
    //load api keys from local json on _userAccountInfo
    auto jsonPath = Paths::ApiKeys;

    rapidjson::Document document;
    if (!BAJson::parseFile(jsonPath, document)) {
        std::cout << "Error loading api keys!" << std::endl;
        return;
    }

    std::string exchangesKey = "exchanges";
    if(BAJson::exists(document,exchangesKey)) {
        auto exchangesJson = document[exchangesKey.c_str()].GetArray();
        std::string binanceKey = "binance";
        for(auto ex = exchangesJson.Begin(); ex != exchangesJson.End(); ex++){
            if (BAJson::exists(ex->GetObject(), binanceKey)) {
                auto binanceJson = ex->GetObject()[binanceKey.c_str()].GetObject();

                auto pk = BAJson::getString(binanceJson,"api_key","");
                auto sk = BAJson::getString(binanceJson,"secret_key","");

                if(!pk.empty())
                    _privateKey = pk;

                if(!sk.empty())
                    _secretKey = sk;
            }
        }
    }

}

const std::string &DBManager::getPrivateKey() {
    return _privateKey;
}

const std::string &DBManager::getSecretKey() {
    return _secretKey;
}



