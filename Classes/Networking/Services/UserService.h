//
// Created by Maykon Meneghel on 10/01/22.
//

#ifndef UNTITLED1_USERSERVICE_H
#define UNTITLED1_USERSERVICE_H

#include "../APIManager.h"
#include <string>
#include <json/json.h>

class UserService {
private:
    APIManager apiManager = APIManager();
public:
    UserService();
    Json::Value getAccessKey(Json::Value body);
    Json::Value createNewUser(Json::Value body);
    Json::Value updateUser();
    Json::Value deleteUser();
};


#endif //UNTITLED1_USERSERVICE_H
