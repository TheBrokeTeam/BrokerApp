//
// Created by Arthur Abel Motelevicz on 19/12/21.
//

#ifndef BROKERAPP_INDICATOR_H
#define BROKERAPP_INDICATOR_H

#include <vector>
#include <string>
#include "../Tickable.h"
#include "../../Widgets/PlotItem/PlotItem.h"

class Indicator : public Tickable, public PlotItem {
public:
    explicit Indicator(Ticker* ticker);
    virtual ~Indicator();

    //TODO:: this is a main behavior and need attention
    /** For Now calculate will be called at onClose bar */
    virtual void calculate(BarHistory* barHistory);
    void onClose(BarHistory* barHistory) override;
    void onLoad(BarHistory* barHistory) override;
    void resetPlot() override;
    void reset() override;

private:

};

#endif //BROKERAPP_INDICATOR_H
