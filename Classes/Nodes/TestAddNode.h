//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_TESTADDNODE_H
#define BROKERAPP_TESTADDNODE_H


#include "INode.h"
#include "../Widgets/IndicatorsView.h"


class TestAddNode: public INode {
public:
    TestAddNode();
    ~TestAddNode();
    void onRender() override;
    int getResult() const;

//    void setInput(int id, int value) override;
//    int getOutput(int id) override;
//    int getInput(int id) override;

    int _idInput_a;
    int _idInput_b;
    int _idOutput;

    float _result = 0;
    float _input_1 = 0;
    float _input_2 = 0;

};


#endif //BROKERAPP_TESTADDNODE_H
