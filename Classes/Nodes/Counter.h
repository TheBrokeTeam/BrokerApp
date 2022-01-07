//
// Created by Arthur Abel Motelevicz on 05/01/22.
//

#ifndef BROKERAPP_COUNTER_H
#define BROKERAPP_COUNTER_H

#include <memory>
#include "../Helpers/graph.h"
#include "INode.h"


class Counter : public INode{
public:
    Counter(StrategyEditor* nodeEditor);
    ~Counter();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    int getRootNodeConnectionsNumber() override;

private:
    int _idInput;
    int _counter = 0;
};


#endif //BROKERAPP_COUNTER_H
