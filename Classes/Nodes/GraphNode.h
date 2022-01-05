//
// Created by Arthur Abel Motelevicz on 04/01/22.
//

#ifndef BROKERAPP_GRAPHNODE_H
#define BROKERAPP_GRAPHNODE_H


#include "INode.h"
#include <stack>

enum class NodeType
{
    ADD,
    RESULT,
    VALUE
};

enum class UiNodeType
{
    ADD,
    RESULT
};

class UiNode : public INode
{
public:
    UiNode(){}

    virtual ~UiNode(){

    };

    UiNodeType type;
    virtual void onRender(float dt) override{};
    virtual void handleStack(std::stack<float>& stack) = 0;
};

struct GraphNode {
    UiNode* onwer{nullptr};
    NodeType type;
    float value;
    explicit GraphNode(const NodeType t,UiNode* o = nullptr) : type(t), value(0.f), onwer(o) {}
    GraphNode(const NodeType t, const float v) : type(t), value(v) {}
};


#endif //BROKERAPP_GRAPHNODE_H
