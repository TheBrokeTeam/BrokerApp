//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_INODE_H
#define BROKERAPP_INODE_H

#include <string>
#include <imgui.h>
#include <vector>

class INode {
public:
    inline static int current_id = 0;
    INode();
    virtual ~INode();
    virtual void onRender();
    void render();
    bool hasInput(int id);
    bool hasOutput(int id);

    virtual void setInput(int id, void* value) = 0;
    virtual void* getOutput(int id) = 0;
    virtual void* getInput(int id) = 0;

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


#endif //BROKERAPP_INODE_H
