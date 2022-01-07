////
//// Created by Arthur Abel Motelevicz on 03/01/22.
////

#ifndef BROKERAPP_CROSSNODE_H
#define BROKERAPP_CROSSNODE_H

#include "INode.h"

class CrossNode : public INode {
public:
    CrossNode(StrategyEditor* nodeEditor);
    ~CrossNode();
    void onRender(float dt) override;
    void handleStack(std::stack<float>& stack) override;
    void endEvaluate() override;

private:
    int _idInput1;
    int _idInput2;

    double _currentInput1 = 0;
    double _currentInput2 = 0;
    double _lastInput1 = 0;
    double _lastInput2 = 0;

    bool _isCrossUp = true;
    bool _output = false;
    int _countCross = 0;
};


#endif //BROKERAPP_CROSSNODE_H
