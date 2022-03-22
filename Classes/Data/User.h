//
// Created by Maykon Meneghel on 23/02/22.
//

#ifndef BROKERAPP_USER_H
#define BROKERAPP_USER_H

#include <string>
#include "../Networking/http/Services/UserService.h"

class User
{
private:
    bool isAuthenticated = false;

protected:
    static User* User_;
    std::string id_;

public:
    User(User &other) = delete;
    void operator=(const User &) = delete;
    static User *GetInstance(const std::string&);
    std::string id() const;

    explicit User(std::string);
};

#endif //BROKERAPP_USER_H