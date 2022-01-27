//
// Created by Maykon Meneghel on 23/01/22.
//

#ifndef BROKERAPP_KLINESERVICE_H
#define BROKERAPP_KLINESERVICE_H


#include "../APIManager.h"
#include "../../Data/Symbol.h"

class KLineService {
private:
    APIManager apiManager = APIManager();
public:
    KLineService();
    rapidjson::Document fetchData(const std::string&, const std::string&, long, long, int);
};


#endif //BROKERAPP_KLINESERVICE_H