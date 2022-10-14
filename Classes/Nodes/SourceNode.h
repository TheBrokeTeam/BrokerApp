//
// Created by Arthur Abel Motelevicz on 04/07/22.
//

#ifndef BROKERAPP_SOURCENODE_H
#define BROKERAPP_SOURCENODE_H
#include "INode.h"

class SourceNode : public INode {
public:
    SourceNode(StrategyEditor* strategyEditor);
    ~SourceNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    int getRootNodeConnectionsNumber() override;
private:
};



#endif //BROKERAPP_SOURCENODE_H
