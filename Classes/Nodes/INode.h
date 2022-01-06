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

enum class NodeType
{
    ADD,
    SMA,
    RESULT,
    VALUE
};

enum class UiNodeType
{
    ADD,
    SMA,
    RESULT
};


class INode {
public:
    INode();
    virtual ~INode();

    virtual void handleStack(std::stack<float>& stack) = 0;
    virtual void onRender(float dt) = 0;

    void render(float dt);
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
};

struct GraphNode {
    INode* owner{nullptr};
    NodeType type;
    float value;
    explicit GraphNode(const NodeType t,INode* o = nullptr) : type(t), value(0.f), owner(o) {}
    GraphNode(const NodeType t, const float v) : type(t), value(v) {}
};


#endif //BROKERAPP_INODE_H
