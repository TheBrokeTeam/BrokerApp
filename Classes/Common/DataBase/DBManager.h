//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#ifndef BROKERAPP_DBMANAGER_H
#define BROKERAPP_DBMANAGER_H

#include "../../Data/AccountInfo.h"
//#include "../../Data/User.h"

class DBManager {
    public:
    DBManager();
    ~DBManager();
//    static void saveUserData(const rapidjson::Document&);
    const AccountInfo& loadUserAccountInfo();
    void updateUserData(const AccountInfo& info);
    const std::string& getPrivateKey();
    const std::string& getSecretKey();
//    bool userSelected();
//    User* getUser();

private:
    std::string _privateKey{""};
    std::string _secretKey{""};

//    User* loadUserData();
    void loadKeys();
    AccountInfo _userAccountInfo;
//    User* _user{nullptr};
};


#endif //BROKERAPP_DBMANAGER_H
