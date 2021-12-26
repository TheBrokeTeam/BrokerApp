//
// Created by Arthur Abel Motelevicz on 26/12/21.
//

#ifndef BROKERAPP_WORKSPACE_H
#define BROKERAPP_WORKSPACE_H


#include "../Editor.h"

class Workspace : public Widget
{
public:
    Workspace(Editor* editor);

    void updateVisible(float dt) override;
    void onPushStyleVar();  // Called just before ImGui::Begin()
    void onPushStyleColor();  // Called just before ImGui::Begin()

    int getWindowFlags() override;

private:
};


#endif //BROKERAPP_WORKSPACE_H
