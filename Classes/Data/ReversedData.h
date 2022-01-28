//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_REVERSEDDATA_H
#define BROKERAPP_REVERSEDDATA_H

#include <vector>

template<typename T, int N = 1>
class ReversedData {
public:
    ReversedData(){
        for(int i = 1; i <= N; i++)
            _data.push_back(std::vector<T>());
    };

    ~ReversedData(){
        clear();
    };

    T& operator()(int reversedIndex, int n = 0){
        auto it = _data[n].begin();
        std::advance(it, fixedIndex(reversedIndex, n));
        return const_cast<T&>(*it);
    }

    int fixedIndex(int reversedIndex, int n = 0)
    {
        assert(reversedIndex >= 0 && reversedIndex< _data[n].size() && "Reversed Index out of bounds");
        int fixedIndex = std::max<int>(0,_data[n].size() - 1 - reversedIndex);
        fixedIndex = std::min<int>(fixedIndex,_data[n].size() - 1);
        return fixedIndex;
    }

    int size(){
        return _data[0].size();
    }

    std::vector<T>& getData(int n = 0){
        return _data[n];
    }

    void push(T val, int n = 0){
        return _data[n].push_back(val);
    }

    void clear(){
        for(auto& v : _data)
            v.clear();
    }

private:
    std::vector<std::vector<T>> _data;
};


#endif //BROKERAPP_REVERSEDDATA_H
