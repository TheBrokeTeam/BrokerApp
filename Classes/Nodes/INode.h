//
// Created by Arthur Abel Motelevicz on 02/01/22.
//

#ifndef BROKERAPP_INODE_H
#define BROKERAPP_INODE_H

#include <string>
#include <imgui.h>
#include <vector>
#include <variant>
#include <map>

class INode {
public:
    inline static int current_id = 0;
    INode();
    virtual ~INode();

    virtual void onRender(float dt) = 0;
    void render(float dt);
    bool hasInput(int id);
    bool hasOutput(int id);
    int getId() const{
        return _id;
    }

    double getValueFromId(int id)
    {
        auto it = _map.find(id);
        if(it != _map.end()) {
            auto v = _map.at(id);
            return v;
        }
        assert(false);
    }

    void setValueForId(int id, double newValue)
    {
        auto it = _map.find(id);
        if(it != _map.end()) {
            it->second = newValue;
            return;
        }
        assert(false);
    }

protected:
    void setName(const std::string& name);
    int generateId();
    int addInput();
    int addOutput();
    std::map<int,double> _map;

private:
    int _id;
    std::string _name = "Node name";
    ImVec2 pos;
    bool _init = false;
    std::vector<int> _inputIds;
    std::vector<int> _outputIds;
};


#endif //BROKERAPP_INODE_H
