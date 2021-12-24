//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CHARTS_H
#define BROKERAPP_CHARTS_H

#include "Widget.h"

class Charts : public Widget {
public:
    Charts(Editor* editor);
    void updateVisible(float dt) override;
};

#endif //BROKERAPP_CHARTS_H
