//
// Created by Maykon Meneghel on 28/01/22.
//

#ifndef BROKERAPP_CONNECTVIEW_H
#define BROKERAPP_CONNECTVIEW_H


#include "Widget.h"

class ConnectView : public Widget {
public:
    explicit ConnectView(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
};

#endif //BROKERAPP_CONNECTVIEW_H
