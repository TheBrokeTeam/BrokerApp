//
// Created by Arthur Abel Motelevicz on 13/01/22.
//

#ifndef BROKERAPP_DOWNSEQUENCENODE_H
#define BROKERAPP_DOWNSEQUENCENODE_H


#include "INode.h"
#include "../Tickers/Ticker.h"

class DownSequenceNode : public INode {
public:
    DownSequenceNode(StrategyEditor* nodeEditor,Ticker* ticker);
    ~DownSequenceNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

private:
    Ticker* _ticker{nullptr};
    int _sequence = 5;
};



#endif //BROKERAPP_DOWNSEQUENCENODE_H
