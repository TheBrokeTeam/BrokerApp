//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_SIMULATIONCONTROLLER_H
#define BROKERAPP_SIMULATIONCONTROLLER_H


#include "Widget.h"

class SimulationController :public Widget {
public:
   explicit SimulationController(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
};


#endif //BROKERAPP_SIMULATIONCONTROLLER_H
