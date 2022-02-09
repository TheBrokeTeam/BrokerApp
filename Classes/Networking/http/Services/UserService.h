//
// Created by Maykon Meneghel on 10/01/22.
//

#ifndef UNTITLED1_USERSERVICE_H
#define UNTITLED1_USERSERVICE_H

#include "../APIManager.h"
#include <string>

class UserService {
private:
    APIManager apiManager = APIManager();
public:
    UserService();
    rapidjson::Document getAccessKey(const rapidjson::Document& body);
    rapidjson::Document createNewUser(const rapidjson::Document& body);
    rapidjson::Document updateUser();
    rapidjson::Document deleteUser();
};


#endif //UNTITLED1_USERSERVICE_H
