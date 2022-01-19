//
// Created by Arthur Abel Motelevicz on 12/01/22.
//

#ifndef BROKERAPP_UPSEQUENCENODE_H
#define BROKERAPP_UPSEQUENCENODE_H

#include "INode.h"
#include "../Tickers/Ticker.h"

class UpSequenceNode : public INode {
public:
    UpSequenceNode(StrategyEditor* nodeEditor,Ticker* ticker);
    ~UpSequenceNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

private:
    Ticker* _ticker{nullptr};
    int _sequence = 5;
};


#endif //BROKERAPP_UPSEQUENCENODE_H
