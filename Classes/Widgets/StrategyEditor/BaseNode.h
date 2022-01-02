//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_BASENODE_H
#define BROKERAPP_BASENODE_H

#include <string>
#include <imgui.h>

class BaseNode {
public:
    inline static int current_id = 0;
    BaseNode();
    virtual ~BaseNode();
    virtual void onRender();
    void render();

protected:
    void setName(const std::string& name);
private:
    int _id;
    std::string _name = "Node name";
    ImVec2 pos;
    bool _init = false;
};


#endif //BROKERAPP_BASENODE_H
