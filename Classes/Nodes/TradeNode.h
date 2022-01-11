//
// Created by Arthur Abel Motelevicz on 07/01/22.
//

#ifndef BROKERAPP_TRADENODE_H
#define BROKERAPP_TRADENODE_H

#include "INode.h"
#include "../Tickables/Strategies/Strategy.h"
#include "../Tickables/Strategies/TradeNodeStrategy.h"

class TradeNode : public INode {
public:
    TradeNode(StrategyEditor* nodeEditor,TradeNodeStrategy* strategy);
    ~TradeNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    int getRootNodeConnectionsNumber() override;

private:
    int _idInputLong;
    int _idInputShort;
    TradeNodeStrategy* _strategy{nullptr};
};


#endif //BROKERAPP_TRADENODE_H
