//
// Created by Maykon Meneghel on 10/01/22.
//

#ifndef UNTITLED1_USERSERVICE_H
#define UNTITLED1_USERSERVICE_H

#include "../APIManager.h"
#include <string>

#ifdef _WIN32
static int platform = 1;
#elif _WIN64
static int platform= 1;
#elif __linux__
static int platform = 2;
#elif __APPLE__
static int platform = 3;
#else
static int platform = 0;
#endif

class UserService {
private:
    APIManager apiManager = APIManager();
    static void openPlatform(const std::string&);
public:
    UserService();
    rapidjson::Document authenticate(const rapidjson::Document& body);
    rapidjson::Document deleteUser();
    void openAuth(const std::string& provider);
    rapidjson::Document logout();
};


#endif //UNTITLED1_USERSERVICE_H
