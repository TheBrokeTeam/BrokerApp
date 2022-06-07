//
// Created by Maykon Meneghel on 28/04/22.
//

#ifndef BROKERAPP_PARSABLE_H
#define BROKERAPP_PARSABLE_H

#include <rapidjson/document.h>

class Parsable {
public:
    virtual rapidjson::Document toJson() = 0;
    virtual void Parse(rapidjson::Value&) = 0;
};


#endif //BROKERAPP_PARSABLE_H
