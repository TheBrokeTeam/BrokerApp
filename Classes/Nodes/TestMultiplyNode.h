//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_TESTMULTIPLYNODE_H
#define BROKERAPP_TESTMULTIPLYNODE_H

#include "INode.h"

class TestMultiplyNode : public INode {
public:
    TestMultiplyNode();
    ~TestMultiplyNode();
    void onRender(float dt) override;

    int _idInput_a;
    int _idInput_b;
    int _idOutput;

    int _result = 0;

};


#endif //BROKERAPP_TESTMULTIPLYNODE_H