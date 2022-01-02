//
// Created by Arthur Abel Motelevicz on 01/01/22.
//

#ifndef BROKERAPP_BASENODE_H
#define BROKERAPP_BASENODE_H

#include <string>
#include <imgui.h>
#include <vector>

class BaseNode {
public:
    inline static int current_id = 0;
    BaseNode();
    virtual ~BaseNode();
    virtual void onRender();
    void render();
    bool hasInput(int id);
    bool hasOutput(int id);

    virtual void setInput(int id, int value);
    virtual int getOutput(int id);
    virtual int getInput(int id);

protected:
    void setName(const std::string& name);
    int generateId();
    int addInput();
    int addOutput();

private:
    int _id;
    std::string _name = "Node name";
    ImVec2 pos;
    bool _init = false;
    std::vector<int> _inputIds;
    std::vector<int> _outputIds;

};


#endif //BROKERAPP_BASENODE_H
