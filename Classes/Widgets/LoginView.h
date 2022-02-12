//
// Created by Maykon Meneghel on 09/02/22.
//

#ifndef BROKERAPP_LOGINVIEW_H
#define BROKERAPP_LOGINVIEW_H


#include "Widget.h"

class LoginView : public Widget{
public:
    LoginView(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

private:
    bool _onLogin = false;
};


#endif //BROKERAPP_LOGINVIEW_H
