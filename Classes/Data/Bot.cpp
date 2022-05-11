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

Bot::Bot(Symbol symbol, StrategyEditor* strategyEditor, StrategyInfo strategyInfo, const std::string& createdBy, const std::string& updatedAt): _symbol(std::move(symbol)), _strategyInfo(strategyInfo)
{
    this->_id = "";
    this->_strategyEditor = std::move(strategyEditor);
    this->_createdBy = createdBy;
    this->_updatedAt = updatedAt;
    this->_name = "Unamed";

//    std::string nodeNames;
//    for(auto node: _nodes)
//    {
//        for(int i=0; i<3; i++)
//            nodeNames.push_back(node.name[i]);
//    }
//    this->_name = _symbol.getCode() + _symbol.getInterval() + nodeNames;
}

//Bot::Bot(const BotInfo& info): _symbol(info.symbol)
//{
//    this->_id = info.id;
//    this->_name = info.name;
//    this->_strategyEditor = info.strategyEditor;
//    this->_createdBy = info.createdBy;
//    this->_updatedAt = info.updatedAt;
//}

Symbol Bot::GetSymbol()
{
    return _symbol;
}

std::string Bot::GetName()
{
    return _name;
}

//std::vector<NodeInfo> Bot::GetNodes()
//{
//    return _nodes;
//}

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

    rapidjson::Document jsonStrategyEditor = _strategyEditor->toJson();
    BAJson::set(doc, "strategyEditor", jsonStrategyEditor);

    std::cout <<  BAJson::stringfy(doc) << std::endl;

    return doc;
}

StrategyInfo Bot::toStrategyInfo(const rapidjson::Value& value)
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

    StrategyInfo strategyInfo(symbol);
    assert(value.IsObject());

    strategyInfo.id = BAJson::getString(value, "_id");
    strategyInfo.name = BAJson::getString(value, "name", "No named");
    strategyInfo.updatedAt = BAJson::getString(value, "updatedAt");
    strategyInfo.createdBy = BAJson::getString(value, "createdBy");

    const rapidjson::Value& strategyEditorJson = value["strategyEditor"].GetObject();
    assert(strategyEditorJson.IsObject());

    const rapidjson::Value& jsonNodes = strategyEditorJson["nodes"].GetArray();
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
        strategyInfo.nodesInfo.push_back(nodeInfo);
    }
    return strategyInfo;
}

//std::vector<BotInfo> Bot::toInfo(const rapidjson::Value& value)
//{
//    std::vector<BotInfo> output;
//
//    assert(value.IsObject());
//
//    std::string id = BAJson::getString(value, "_id");
//    std::string name = BAJson::getString(value, "name", "No named");
//    std::string updatedAt = BAJson::getString(value, "updatedAt");
//    std::string createdBy = BAJson::getString(value, "createdBy");
//
//    const rapidjson::Value& jsonSymbol = value["symbol"].GetObject();
//    assert(jsonSymbol.IsObject());
//    std::string code = BAJson::getString(jsonSymbol, "code");
//    std::string interval = BAJson::getString(jsonSymbol, "interval");
//
//    const rapidjson::Value& range = jsonSymbol["range"].GetObject();
//    assert(range.IsObject());
//
//    long start = BAJson::getLong(range, "start");
//    long end = BAJson::getLong(range, "end");
//
//    Symbol symbol = Symbol(code, interval,start,end);
//
//    const rapidjson::Value& jsonNodes = value["nodes"].GetArray();
//    assert(jsonNodes.IsArray());
//
//    rapidjson::GenericArray jsonNodesArray = jsonNodes.GetArray();
//
//    std::vector<NodeInfo> infos;
//    for(const auto& jsonNode: jsonNodesArray) {
//
//        std::string nodeName = jsonNode["name"].GetString();
//        int nodeId = jsonNode["id"].GetInt();
//        std::string nodeEditorId = jsonNode["nodeEditor"].GetString();
//        bool _init = jsonNode["_init"].GetBool();
//        bool isIndicatorNode = jsonNode["isIndicatorNode"].GetBool();
//        int icon = jsonNode["icon"].GetInt();
//
//        UiNodeType uiNodeType = INode::stringToUiNodeType(jsonNode["nodeType"].GetString());
//
//        const rapidjson::Value& internalNodesArray = jsonNode["internalNodes"].GetArray();
//        assert(internalNodesArray.IsArray());
//        std::vector<int> internalNodes;
//
//        for(auto& internalNode: internalNodesArray.GetArray()){
//            internalNodes.push_back(internalNode.GetInt());
//        }
//
//        std::vector<float> position = BAJson::getFloatVector(jsonNode, "position");
//        ImVec2 pos = ImVec2(position[0], position[1]);
//
////        std::map<std::string, std::vector<graph::Span<const int>>> internalEdges = std::map<std::string, std::vector<graph::Span<const int>>>();
//
//        infos.push_back({
//            nodeId,
//            uiNodeType,
//            pos,
//            nodeName,
//            internalNodes,
//            _init,
//            isIndicatorNode,
//            icon
//        });
//
//    }
//    output.push_back({id, name, symbol, infos, createdBy, updatedAt});
//
//    return output;
//}
StrategyInfo::StrategyInfo(Symbol symbol): symbol(symbol) {

}
