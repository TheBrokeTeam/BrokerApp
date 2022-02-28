//
// Created by Arthur Abel Motelevicz on 21/02/22.
//

#ifndef BROKERLIB_INDICATOR_H
#define BROKERLIB_INDICATOR_H

#include <iostream>
#include <vector>
#include <string>
#include "../Tickables/Tickable.h"

class IndicatorData : public Tickable {
public:
    explicit IndicatorData(Ticker* ticker);
    virtual ~IndicatorData();
    virtual void calculate(BarHistory* barHistory) = 0;
    void onClose(BarHistory* barHistory) override;
    void onLoad(BarHistory* barHistory) override;
    void reset() override;
    Ticker* getTicker();
    const std::vector<double>& getTime(){
        return _time;
    }
protected:
    std::vector<double> _time;
private:
};


#endif //BROKERLIB_INDICATOR_H
