//
// Created by Maykon Meneghel on 09/02/22.
//

#ifndef BROKERAPP_LOGINVIEW_H
#define BROKERAPP_LOGINVIEW_H


#include "Widget.h"
#include "../Networking/Server/HttpServer.h"
#include "../Contexts/Context.h"
#include "SubWidgets/Spinner.h"
#include "../Networking/API/Services/UserService.h"

class LoginView : public Widget{
public:
    LoginView(Context* context);
    void updateVisible(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;
private:
    void openAuthProvider(const std::string&);
    void Cancel();
};


#endif //BROKERAPP_LOGINVIEW_H
