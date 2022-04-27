//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_BOT_H
#define BROKERAPP_BOT_H

#include <rapidjson/document.h>
#include "../Nodes/INode.h"
#include "Symbol.h"

class Bot {
private:
    std::string _name;
    std::string _createdBy;
    Symbol _symbol;
    std::vector<std::shared_ptr<INode>> _nodes;
    std::string _updatedAt;
public:
    Bot(const std::string& name, Symbol symbol, std::vector<std::shared_ptr<INode>> nodes, const std::string& createdBy, const std::string& updatedAt);

    rapidjson::Document toJson();
    static Bot Parse(const rapidjson::Value&);
    rapidjson::Document save();

    std::string GetName();
    Symbol GetSymbol();
    std::vector<std::shared_ptr<INode>> GetNodes();
    std::string GetUpdatedTime();
};


#endif //BROKERAPP_BOT_H
