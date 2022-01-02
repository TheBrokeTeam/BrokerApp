//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_TESTRESULTNODE_H
#define BROKERAPP_TESTRESULTNODE_H


#include "Node.h"
#include "../Widgets/IndicatorsView.h"


class TestResultNode: public Node<int> {
public:
    TestResultNode();
    ~TestResultNode();
    void onRender() override;
    void setInput(int id,int value) override;
    int _idInput;
    int _input{0};
};

#endif //BROKERAPP_TESTRESULTNODE_H
