//
// Created by Arthur Abel Motelevicz on 28/12/21.
//

#ifndef BROKERAPP_REVERSEDDATA_H
#define BROKERAPP_REVERSEDDATA_H

#include <vector>

template<typename T>
class ReversedData {
public:
    //Warning:: this cannot be populate using = operator.
    //It wont change the value inside array. Ex: T[i] = value; will not work.
    T& operator[](int reversedIndex){
        auto it = _data.begin();
        std::advance(it, fixedIndex(reversedIndex));
        return const_cast<T&>(*it);
    }

    int fixedIndex(int reversedIndex)
    {
        assert(reversedIndex >= 0 && reversedIndex< _data.size() && "Reversed Index out of bounds");
        int fixedIndex = std::max<int>(0,_data.size() - 1 - reversedIndex);
        fixedIndex = std::min<int>(fixedIndex,_data.size() - 1);
        return fixedIndex;
    }

protected:
    std::vector<T> _data;
};


#endif //BROKERAPP_REVERSEDDATA_H
