//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_INDICATORS_H
#define BROKERAPP_INDICATORS_H

#include "Widget.h"

class Indicators : public Widget {
public:
    Indicators(Editor* editor);
    void updateVisible(float dt) override;
private:
};


#endif //BROKERAPP_INDICATORS_H
