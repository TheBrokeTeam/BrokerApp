//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_TESTNODE_H
#define BROKERAPP_TESTNODE_H


class TestNode {
public:
    inline static int current_id = 0;
    TestNode();
    void render();

private:
    int _id;
    int _idInput;
    int _idOutput;


};


#endif //BROKERAPP_TESTNODE_H
