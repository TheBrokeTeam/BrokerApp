//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#include "DBManager.h"
#include "Paths.h"
#include "../Json/BAJson.h"

DBManager::DBManager() {
    loadKeys();
//    loadUserData();
}

DBManager::~DBManager() = default;

//void DBManager::saveUserData(const rapidjson::Document& doc) {
//    if(!std::filesystem::exists(Paths::Root))
//    {
//        std::filesystem::create_directory(Paths::Root);
//    }
//
//    if(!std::filesystem::exists(Paths::UserData))
//    {
//        BAJson::save(doc, Paths::UserData);
//    }
//}

//User* DBManager::loadUserData() {
//    if(std::filesystem::exists(Paths::UserData)) {
//        rapidjson::Document user_doc;
//        user_doc.SetObject();
//        BAJson::parseFile(Paths::UserData, user_doc);
//        _user = new User(user_doc);
//    } else {
//        _user = nullptr;
//    }
//    return _user;
//}

const AccountInfo&  DBManager::loadUserAccountInfo() {
    //load the info on _userAccountInfo
    return _userAccountInfo;
}

void DBManager::updateUserData(const AccountInfo &info) {
    //update info on _userAccountInfo
    _userAccountInfo.update(info);
}

void DBManager::loadKeys() {
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
//
//bool DBManager::userExists() {
//    return (_user != nullptr) ? true : false;
//}
//
//User* DBManager::getUser()
//{
//    return _user;
//}


