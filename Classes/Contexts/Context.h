//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_CONTEXT_H
#define BROKERAPP_CONTEXT_H

#include <vector>
#include "../Data/BarData.h"

class Context {
    public:
        Context();
        ~Context();

        const std::vector<BarData>& getData(){
            return _data;
        }

    std::vector<BarData> _data;
};

#endif //BROKERAPP_CONTEXT_H
