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

Bot::Bot(Symbol symbol, std::vector<NodeInfo> nodes, const std::string& createdBy, const std::string& updatedAt): _symbol(std::move(symbol))
{
    this->_id = "";
    this->_nodes = std::move(nodes);
    this->_createdBy = createdBy;
    this->_updatedAt = updatedAt;
    std::string nodeNames;
    for(auto node: _nodes)
    {
        for(int i=0; i<3; i++)
            nodeNames.push_back(node.name[i]);
    }
    this->_name = _symbol.getCode() + _symbol.getInterval() + nodeNames;
}

Bot::Bot(const BotInfo& info): _symbol(info.symbol)
{
    this->_id = info.id;
    this->_name = info.name;
    this->_nodes = info.nodes;
    this->_createdBy = info.createdBy;
    this->_updatedAt = info.updatedAt;
}

Symbol Bot::GetSymbol()
{
    return _symbol;
}

std::string Bot::GetName()
{
    return _name;
}

std::vector<NodeInfo> Bot::GetNodes()
{
    return _nodes;
}

std::string Bot::GetUpdatedTime()
{
    return _updatedAt;
}

std::string Bot::GetId()
{
    return _id;
}

rapidjson::Document Bot::Save()
{
    auto bootService = new BotService();
    return bootService->saveBot(this->toJson());
}

rapidjson::Document Bot::toJson()
{
    rapidjson::Document doc;
    doc.SetObject();

    BAJson::set(doc, "name", _name);
    BAJson::set(doc, "createdBy", _createdBy);

    rapidjson::Document jsonSymbol = _symbol.toJson();
    BAJson::set(doc, "symbol", jsonSymbol);

    rapidjson::Document jsonNodes;
    jsonNodes.SetArray();
    for(auto& node: _nodes) {
        auto n = node.toJson();
        BAJson::append(jsonNodes, n);
        std::cout << BAJson::stringfy(jsonNodes) << std::endl;
    }

    BAJson::set(doc, "nodes", jsonNodes);

    std::cout <<  BAJson::stringfy(doc) << std::endl;

    return doc;
}

std::vector<BotInfo> Bot::Parse(const rapidjson::Value& value)
{
    std::vector<BotInfo> output;

    assert(value.IsObject());

    std::string id = BAJson::getString(value, "_id");
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

        std::string nodeName = jsonNode["name"].GetString();
        int nodeId = jsonNode["id"].GetInt();
        std::string nodeEditorId = jsonNode["nodeEditor"].GetString();
        bool _init = jsonNode["_init"].GetBool();
        bool isIndicatorNode = jsonNode["isIndicatorNode"].GetBool();
        int icon = jsonNode["icon"].GetInt();

        UiNodeType uiNodeType = INode::stringToUiNodeType(jsonNode["nodeType"].GetString());

        const rapidjson::Value& internalNodesArray = jsonNode["internalNodes"].GetArray();
        assert(internalNodesArray.IsArray());
        std::vector<int> internalNodes;

        for(auto& internalNode: internalNodesArray.GetArray()){
            internalNodes.push_back(internalNode.GetInt());
        }

        std::vector<float> position = BAJson::getFloatVector(jsonNode, "position");
        ImVec2 pos = ImVec2(position[0], position[1]);

        infos.push_back({
            nodeId,
            uiNodeType,
            pos,
            nodeName,
            internalNodes,
            _init,
            isIndicatorNode,
            icon,
            nodeEditorId
        });

    }
    output.push_back({id, name, symbol, infos, createdBy, updatedAt});

    return output;
}
