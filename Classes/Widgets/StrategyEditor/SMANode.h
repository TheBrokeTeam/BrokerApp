//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_SMANODE_H
#define BROKERAPP_SMANODE_H

#include "BaseNode.h"

class SMANode: public BaseNode {
public:
    SMANode();
    void onRender() override;

    int _idInput;
    int _idOutput;
};


#endif //BROKERAPP_SMANODE_H
