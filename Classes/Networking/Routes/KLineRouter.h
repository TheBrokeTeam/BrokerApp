//
// Created by Maykon Meneghel on 23/01/22.
//

#ifndef BROKERAPP_KLINEROUTER_H
#define BROKERAPP_KLINEROUTER_H

#include <string>
#include "../../Data/Symbol.h"
#include "../APIRouter.h"

class KLineRouter {
protected:
    std::string endpoint = "/klines";
public:
    KLineRouter();
    [[nodiscard]] APIRouter getData(Symbol) const;
};


#endif //BROKERAPP_KLINEROUTER_H
