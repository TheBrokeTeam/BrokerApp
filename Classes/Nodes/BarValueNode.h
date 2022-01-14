//
// Created by Arthur Abel Motelevicz on 14/01/22.
//

#ifndef BROKERAPP_BARVALUENODE_H
#define BROKERAPP_BARVALUENODE_H


#include "INode.h"
#include "../Tickers/Ticker.h"

class BarValueNode : public INode {
public:
    BarValueNode(StrategyEditor* nodeEditor,Ticker* ticker);
    ~BarValueNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;

private:
    Ticker* _ticker{nullptr};
};


#endif //BROKERAPP_BARVALUENODE_H
