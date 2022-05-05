//
// Created by Maykon Meneghel on 26/04/22.
//

#include "Bot.h"
#include "../Common/Json/BAJson.h"
#include "../Networking/API/Services/BotService.h"
#include "../Nodes/SMANode.h"
#include "../Nodes/BollingerNode.h"
#include "../Nodes/VWAPNode.h"
#include "../Nodes/CrossNode.h"
#include "../Nodes/Counter.h"
#include "../Tickables/Strategies/TradeNodeStrategy.h"
#include "../Nodes/UpSequenceNode.h"
#include "../Nodes/TradeNode.h"
#include "../Nodes/DownSequenceNode.h"
#include "../Nodes/BarValueNode.h"
#include "../Widgets/ProfitAndLossesView.h"
#include "../Widgets/StrategyEditor.h"

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
        auto n = node->toJson();
        BAJson::append(jsonNodes, n);
        std::cout << BAJson::stringfy(jsonNodes) << std::endl;
    }

    BAJson::set(doc, "nodes", jsonNodes);

    std::cout <<  BAJson::stringfy(doc) << std::endl;

    return doc;
}

std::vector<BotInfo> Bot::Parse(const rapidjson::Value& value) {
    std::vector<BotInfo> output;

    assert(value.IsObject());

    std::string _id = BAJson::getString(value, "_id");
    std::string name = BAJson::getString(value, "name", "No named");
    std::string updatedAt = BAJson::getString(value, "updatedAt");
    std::string createdBy = BAJson::getString(value, "createdBy");

    const rapidjson::Value& jsonSymbol = value["symbol"].GetObject();
    assert(jsonSymbol.IsObject());
    std::string code = BAJson::getString(jsonSymbol, "code");
    std::string interval = BAJson::getString(jsonSymbol, "interval");

    const rapidjson::Value& range = jsonSymbol["range"].GetObject();
    assert(range.IsObject());

    long start = BAJson::getLong(range, "start");
    long end = BAJson::getLong(range, "end");

    Symbol symbol = Symbol(code, interval,start,end);

    const rapidjson::Value& jsonNodes = value["nodes"].GetArray();
    assert(jsonNodes.IsArray());

    rapidjson::GenericArray jsonNodesArray = jsonNodes.GetArray();

    std::vector<NodeInfo> infos;
    for(const auto& jsonNode: jsonNodesArray) {

        UiNodeType uiNodeType = INode::stringToUiNodeType(jsonNode["nodeType"].GetString());
        NodeType nodeType = INode::stringToType(jsonNode["nodeType"].GetString());

        std::vector<float> position = BAJson::getFloatVector(jsonNode, "position");
        ImVec2 pos = ImVec2(position[0], position[1]);

        infos.push_back({uiNodeType, pos});

    }
    output.push_back({name, symbol, infos, createdBy, updatedAt});

    return output;
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
