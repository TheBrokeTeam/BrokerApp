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

enum class NodeType
{
    ADD,
    SMA,
    CROSS,
    CROSS_COUNTER,
    VALUE
};

enum class UiNodeType
{
    ADD,
    SMA,
    CROSS,
    CROSS_COUNTER,
};


class GraphNode;

class INode {
public:
    INode(std::shared_ptr<graph::Graph<GraphNode>> graph);
    virtual ~INode();

    virtual void handleStack(std::stack<float>& stack) = 0;
    virtual void onRender(float dt) = 0;

    int addNode(const GraphNode& node);
    int addEdge(int from, int to);

    int numberOfConnections(int nodeId);
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

    bool getIsIndicatorNode(){
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
protected:
    void setName(const std::string& name);
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
