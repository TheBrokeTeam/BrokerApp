//
// Created by Luiz Veloso on 05/03/22.
//

#ifndef BROKERAPP_SUBPLOTRENDERERDELEGATE_H
#define BROKERAPP_SUBPLOTRENDERERDELEGATE_H


#include "SubplotRenderer.h"

class SubplotRenderer;
class SubplotRendererDelegate {
    virtual void subplotDidScroll(int startIndex, int endIndex, SubplotRenderer *sender) = 0;
};


#endif //BROKERAPP_SUBPLOTRENDERERDELEGATE_H
