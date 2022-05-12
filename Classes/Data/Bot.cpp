//
// Created by Maykon Meneghel on 26/04/22.
//

#include "Bot.h"
#include "../Common/Json/BAJson.h"
#include "../Networking/API/Services/BotService.h"
#include "../Nodes/SMANode.h"
#include "../Nodes/Counter.h"
#include "../Widgets/StrategyEditor.h"
#include <utility>

Bot::Bot(Symbol symbol, StrategyEditor* strategyEditor, const std::string& createdBy, const std::string& updatedAt): _symbol(std::move(symbol))
{
    this->_id = "";
    this->_strategyEditor = strategyEditor;

    for(auto& node: _strategyEditor->getNodes()) {
        auto n = node->toInfo();
        this->_nodesInfo.push_back(n);
    }

    this->_createdBy = createdBy;
    this->_updatedAt = updatedAt;
    this->_name = "Unamed";
}

Bot::Bot(const BotInfo& info): _symbol(info.symbol)
{
    this->_id = info.id;
    this->_nodesInfo = info.nodesInfo;
    this->_name = info.name;
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
    return _nodesInfo;
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

    rapidjson::Document jsonNodes = _strategyEditor ->toJson();
    BAJson::set(doc, "nodes", jsonNodes);

    std::cout <<  BAJson::stringfy(doc) << std::endl;

    return doc;
}

BotInfo Bot::toInfo(const rapidjson::Value& value)
{
    const rapidjson::Value& jsonSymbol = value["symbol"].GetObject();
    assert(jsonSymbol.IsObject());
    std::string code = BAJson::getString(jsonSymbol, "code");
    std::string interval = BAJson::getString(jsonSymbol, "interval");

    const rapidjson::Value& range = jsonSymbol["range"].GetObject();
    assert(range.IsObject());

    long start = BAJson::getLong(range, "start");
    long end = BAJson::getLong(range, "end");

    Symbol symbol = Symbol(code, interval,start,end);

    BotInfo botInfo(symbol);
    assert(value.IsObject());

    botInfo.id = BAJson::getString(value, "_id");
    botInfo.name = BAJson::getString(value, "name", "No named");
    botInfo.updatedAt = BAJson::getString(value, "updatedAt");
    botInfo.createdBy = BAJson::getString(value, "createdBy");

    const rapidjson::Value& jsonNodes = value["nodes"].GetArray();
    assert(jsonNodes.IsArray());

    for(const auto& jsonNode:  jsonNodes.GetArray()) {
        NodeInfo nodeInfo;

        nodeInfo.id = jsonNode["id"].GetInt();
        nodeInfo.name = jsonNode["name"].GetString();
        nodeInfo.nodeType = INode::stringToUiNodeType(jsonNode["nodeType"].GetString());

        std::vector<float> position = BAJson::getFloatVector(jsonNode, "position");
        nodeInfo.position = ImVec2(position[0], position[1]);

        nodeInfo._init = jsonNode["_init"].GetBool();
        nodeInfo.icon = jsonNode["icon"].GetInt();
        nodeInfo.isIndicatorNode = jsonNode["isIndicatorNode"].GetBool();

        const rapidjson::Value &internalNodesArray = jsonNode["internalNodes"].GetArray();
        assert(internalNodesArray.IsArray());

        for (auto &internalNode: internalNodesArray.GetArray()) {
            nodeInfo.internalNodes.push_back(internalNode.GetInt());
        }

        if (jsonNode.HasMember("internalEdges")) {
            const rapidjson::Value &internalEdgesArray = jsonNode["internalEdges"].GetArray();
            assert(internalEdgesArray.IsArray());

            for (auto &internalEdge: internalEdgesArray.GetArray()) {
                for (auto internalNodeId: nodeInfo.internalNodes) {
                    std::string strId = std::to_string(internalNodeId);
                    if (internalEdge.HasMember(strId.c_str())) {
                        const rapidjson::Value &edges = internalEdge[strId.c_str()].GetArray();
                        assert(edges.IsArray());
                        EdgeInfo edgeInfo;
                        edgeInfo.id = internalNodeId;
                        for (auto &edge: edges.GetArray()) {
                            Edge e{};
                            e.from = atoi(edge["from"].GetString());
                            e.to = atoi(edge["to"].GetString());
                            edgeInfo.edges.push_back(e);
                        }
                        nodeInfo.internalEdges.push_back(edgeInfo);
                    }
                }

            }
        }
        botInfo.nodesInfo.push_back(nodeInfo);
    }
    return botInfo;
}

BotInfo::BotInfo(Symbol symbol): symbol(std::move(symbol)) { }
