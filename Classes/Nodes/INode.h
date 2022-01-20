//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_INODE_H
#define BROKERAPP_INODE_H

#include <string>
#include <imgui.h>
#include <vector>
#include <variant>
#include <map>

#include <stack>
#include "../Helpers/graph.h"
#include "../Tickables/Indicators/Indicator.h"

class StrategyEditor;
//Internal Nodes inside th graph
enum class NodeType
{
    SMA,
    EMA,
    BOLL,
    CROSS,
    COUNTER,
    BAR_SEQ_DOWN,
    BAR_SEQ_UP,
    TREND,
    TRADE,
    VALUE
};

//all types of possible nodes rendered on editor (indicators + other nodes)
enum class UiNodeType
{
    SMA,
    EMA,
    BOLL,
    CROSS,
    COUNTER,
    BAR_SEQ_DOWN,
    BAR_SEQ_UP,
    TREND,
    TRADE
};


class GraphNode;


class INode {
public:
    INode(StrategyEditor* strategyEditor);
    virtual ~INode();

    virtual void handleStack(std::stack<float>& stack) = 0;
    virtual void onRender(float dt) = 0;

    int addNode(const GraphNode& node);
    int addEdge(int from, int to);

    int numberOfConnectionsTo(int nodeId);
    int numberOfConnectionsFrom(int nodeId);

    virtual void willStartEvaluate() {};
    virtual void endEvaluate() {};


    GraphNode* getGraphNode(int id);

        //just for root nodes
    virtual int getRootNodeConnectionsNumber(){
        return 0;
    };

    std::shared_ptr<Indicator> getIndicator(){
        return _indicator.lock();
    }

    void  setIndicator(std::shared_ptr<Indicator> indicator){
        _indicator = indicator;
        _isIndicatorNode = true;
    }

    bool getIsIndicatorNode() const{
        return _isIndicatorNode;
    };

    void render(float dt);

    //For customize the title bar.. should be used in pair
    virtual void initStyle();
    virtual void finishStyle();


    int getId() const{
        return _id;
    }
    const UiNodeType& getType();
    void setType(const UiNodeType& type);
    void setIcon(int icon);
protected:
    void setNodeName(const std::string& name);
    int _id;
    UiNodeType _type;

private:
    std::string _name = "Node name";
    ImVec2 pos;
    bool _init = false;
    std::vector<int> _internalNodes;
    std::shared_ptr<graph::Graph<GraphNode>> _graph;
    bool _isIndicatorNode = false;
    std::weak_ptr<Indicator> _indicator;
    StrategyEditor* _nodeEditor{nullptr};
    int _icon{0};
};

class GraphNode {
public:
    INode* owner{nullptr};
    NodeType type;
    float value;
    explicit GraphNode(const NodeType t,INode* o = nullptr) : type(t), value(0.f), owner(o) {}
    GraphNode(const NodeType t, const float v) : type(t), value(v) {}
};


#endif //BROKERAPP_INODE_H
