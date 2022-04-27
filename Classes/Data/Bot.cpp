//
// Created by Maykon Meneghel on 26/04/22.
//

#include "Bot.h"
#include "../Common/Json/BAJson.h"
#include "../Networking/API/Services/BotService.h"

#include <utility>

rapidjson::Document Bot::toJson() {
    rapidjson::Document doc;
    doc.SetObject();

    BAJson::set(doc, "createdBy", _createdBy);

    rapidjson::Document jsonSymbol = _symbol.toJson();
    BAJson::set(doc, "symbol", jsonSymbol);

    rapidjson::Document jsonNodes;
    jsonNodes.SetArray();
    for(const auto& node: _nodes) {
        rapidjson::Document n;
        n.SetObject();
        n = node->toJson();
        jsonNodes.PushBack(n, doc.GetAllocator());
    }

    BAJson::set(doc, "nodes", jsonNodes);

    return doc;
}

Bot Bot::Parse(const rapidjson::Value& value) {
    assert(value.IsObject());

    std::string _id = BAJson::getString(value, "_id");
    std::string name = BAJson::getString(value, "name", "No named");
    std::string updatedAt = BAJson::getString(value, "updatedAt");
    std::string createdBy = BAJson::getString(value, "createdBy");

    const rapidjson::Value& jsonSymbol =value["symbol"].GetObject();
    assert(jsonSymbol.IsObject());
    std::string code = BAJson::getString(jsonSymbol, "code");
    std::string interval = BAJson::getString(jsonSymbol, "interval");

    const rapidjson::Value& range = jsonSymbol["range"].GetObject();
    assert(range.IsObject());

    long start = BAJson::getLong(range, "start");
    long end = BAJson::getLong(range, "end");

    Symbol symbol = Symbol(code, interval,start,end);

    Bot bot = Bot(name,
                  symbol,
                  std::vector<std::shared_ptr<INode>>(),
                  createdBy,
                  updatedAt
    );

    return bot;
}

Bot::Bot(const std::string& name, Symbol symbol, std::vector<std::shared_ptr<INode>> nodes, const std::string& createdBy, const std::string& updatedAt): _name(std::move(name)), _symbol(symbol), _nodes(std::move(nodes)), _createdBy(std::move(createdBy)), _updatedAt(std::move(updatedAt)) {

}

Symbol Bot::GetSymbol() {
    return _symbol;
}

std::string Bot::GetName() {
    return _name;
}

std::vector<std::shared_ptr<INode>> Bot::GetNodes() {
    return _nodes;
}

std::string Bot::GetUpdatedTime() {
    return _updatedAt;
}

rapidjson::Document Bot::save() {
    auto bootService = new BotService();
    return bootService->saveBot(this->toJson());
}
