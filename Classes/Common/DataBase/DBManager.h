//
// Created by Arthur Abel Motelevicz on 19/03/22.
//

#ifndef BROKERAPP_DBMANAGER_H
#define BROKERAPP_DBMANAGER_H

#include "../../Data/AccountInfo.h"

class DBManager {
    public:
    DBManager();
    ~DBManager();
    const AccountInfo& loadUserData();
    void updateUserData(const AccountInfo& info);
    const std::string& getPrivateKey();
    const std::string& getSecretKey();

private:
    std::string _privateKey{""};
    std::string _secretKey{""};

    void loadKeys();
    AccountInfo _userAccountInfo;
};


#endif //BROKERAPP_DBMANAGER_H
