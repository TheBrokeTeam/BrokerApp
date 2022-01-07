//
// Created by Arthur Abel Motelevicz on 05/01/22.
//

#ifndef BROKERAPP_CROSSCOUNTER_H
#define BROKERAPP_CROSSCOUNTER_H

#include <memory>
#include "../Helpers/graph.h"
#include "INode.h"


class CrossCounter : public INode{
public:
    CrossCounter(StrategyEditor* nodeEditor);
    ~CrossCounter();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    int getRootNodeConnectionsNumber();

private:
    int _idInput;
    int _counter = 0;
};


#endif //BROKERAPP_CROSSCOUNTER_H
