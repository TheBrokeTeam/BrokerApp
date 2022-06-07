//
// Created by Maykon Meneghel on 26/04/22.
//

#ifndef BROKERAPP_BOT_H
#define BROKERAPP_BOT_H

#include <rapidjson/document.h>
#include "../Nodes/INode.h"
#include "Symbol.h"

struct BotInfo {
    std::string id;
    std::string name;
    Symbol symbol;
    std::vector<NodeInfo> nodesInfo;
    std::string createdBy;
    std::string updatedAt;
    explicit BotInfo(Symbol symbol);
};

class Bot {
private:
    std::string _id;
    std::string _name;
    Symbol _symbol;
    StrategyEditor* _strategyEditor{};
    std::vector<NodeInfo> _nodesInfo;
    std::string _createdBy;
    std::string _updatedAt;

public:
    Bot(Symbol symbol, StrategyEditor* strategyEditor, const std::string& createdBy, const std::string& updatedAt);
    explicit Bot(const BotInfo& info);

    rapidjson::Document toJson();
    static BotInfo toInfo(const rapidjson::Value&);
    rapidjson::Document Save();

    std::string GetName();
    std::string GetId();
    Symbol GetSymbol();
    std::vector<NodeInfo> GetNodes();
    std::string GetUpdatedTime();

};


#endif //BROKERAPP_BOT_H
