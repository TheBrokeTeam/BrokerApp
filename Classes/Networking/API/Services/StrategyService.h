//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_STRATEGYSERVICE_H
#define BROKERAPP_STRATEGYSERVICE_H

#include "../APIManager.h"

class StrategyService {
private:
    APIManager apiManager = APIManager();

public:
    StrategyService();
    rapidjson::Document saveStrategy(const rapidjson::Document&);
    rapidjson::Document deleteStrategy(const std::string&);
    rapidjson::Document fetchStrategies(const std::string&);
};


#endif //BROKERAPP_STRATEGYSERVICE_H
