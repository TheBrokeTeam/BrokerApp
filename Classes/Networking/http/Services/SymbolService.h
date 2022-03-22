//
// Created by Maykon Meneghel on 07/01/22.
//

#ifndef UNTITLED1_SYMBOLSERVICE_H
#define UNTITLED1_SYMBOLSERVICE_H

#include "../APIManager.h"
#include <string>

class SymbolService {
private:
    APIManager apiManager = APIManager();
public:
    SymbolService();
    rapidjson::Document fetchDataByCode(const std::string& code);
    rapidjson::Document fetchAllSymbols();
};


#endif //UNTITLED1_SYMBOLSERVICE_H
