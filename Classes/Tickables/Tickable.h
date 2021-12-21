//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_TICKABLE_H
#define BROKERAPP_TICKABLE_H


#include "../Data/BarData.h"
#include "../Data/TickData.h"
#include "../Data/Symbol.h"

class Tickable {
public:
    virtual void onOpen(const TickData &tickData);
    virtual void onClose(const TickData &tickData);
    virtual void onTick(const TickData &tickData);
    virtual void onLoad(std::shared_ptr<Symbol> symbol);
    virtual void reset();

    double time(int indexBar);
    double volume(int indexBar);
    double open(int indexBar);
    double high(int indexBar);
    double low(int indexBar);
    double close(int indexBar);

    int size();

protected:
    std::vector<BarData> _data;
    int _currentIndex = 0;
    std::shared_ptr<Symbol> _symbol{nullptr};
private:
    int fixedIndex(int reversedIndex);
};


#endif //BROKERAPP_TICKABLE_H
