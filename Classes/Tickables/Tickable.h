//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKABLE_H
#define BROKERAPP_TICKABLE_H

#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"
#include "../Contexts/Context.h"
#include "../Data/BarHistory.h"

class Tickable {
public:
    Tickable(Context* context,std::shared_ptr<Symbol> symbol);

    virtual void onOpen(BarHistory* barHistory);
    virtual void onClose(BarHistory* barHistory);
    virtual void onTick(BarHistory* barHistory);
    virtual void onLoad(std::shared_ptr<Symbol> symbol);

protected:
    std::shared_ptr<Symbol> _symbol{nullptr};
    Context* _context{nullptr};
private:
};


#endif //BROKERAPP_TICKABLE_H
