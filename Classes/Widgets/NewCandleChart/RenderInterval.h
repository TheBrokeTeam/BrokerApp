//
// Created by Luiz Veloso on 05/03/22.
//

#ifndef BROKERAPP_RENDERINTERVAL_H
#define BROKERAPP_RENDERINTERVAL_H


class RenderInterval {
public:
    int startIndex = 0;
    int endIndex = 1000;
    int size() const {
        return endIndex - startIndex + 1;
    }
};


#endif //BROKERAPP_RENDERINTERVAL_H
