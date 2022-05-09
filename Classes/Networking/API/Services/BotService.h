//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_BOTSERVICE_H
#define BROKERAPP_BOTSERVICE_H

#include "../APIManager.h"

class BotService {
private:
    APIManager apiManager = APIManager();

public:
    BotService();
    rapidjson::Document saveBot(const rapidjson::Document &bot);
    rapidjson::Document deleteBot(const std::string &id);
    rapidjson::Document fetchBots(const std::string &userId);
};


#endif //BROKERAPP_BOTSERVICE_H
