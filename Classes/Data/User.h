//
// Created by Maykon Meneghel on 23/02/22.
//

#ifndef BROKERAPP_USER_H
#define BROKERAPP_USER_H

#include <string>
#include "../Networking/API/Services/UserService.h"

class User
{
private:
    std::string _id;
    std::string _token;
    std::string _name{""};

public:
    explicit User(const std::string&, const std::string&);
    User(const rapidjson::Document&);
    ~User() = delete;

    const char* GetName();
};


#endif //BROKERAPP_USER_H