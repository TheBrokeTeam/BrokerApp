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
    enum class Type{
        Bool,
        Int,
        Float,
        Double
    };
    typedef std::variant<bool, int, float, double> node_values;
    struct TypeValue
    {
        Type type;
        node_values value;
    };


    inline static int current_id = 0;
    INode();
    virtual ~INode();

    virtual void onRender();
    void render();
    bool hasInput(int id);
    bool hasOutput(int id);

    template<typename T>
    T getValueFromId(int id)
    {
        auto it = _map.find(id);
        if(it != _map.end()) {
            auto v = _map.at(id);
            return std::get<T>(v.value);
        }
        assert(false);
        return 0;
    }

    template<typename T>
    void setValueForId(int id, T newValue)
    {
        auto it = _map.find(id);
        if(it != _map.end()) {
            it->second.value = newValue;
            return;
        }
        assert(false);
    }

protected:
    void setName(const std::string& name);
    int generateId();
    int addInput(const Type& type);
    int addOutput(const Type& type);
    std::map<int,TypeValue> _map;

private:
    int _id;
    std::string _name = "Node name";
    ImVec2 pos;
    bool _init = false;
    std::vector<int> _inputIds;
    std::vector<int> _outputIds;



};


#endif //BROKERAPP_INODE_H
