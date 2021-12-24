//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CANDLECHART_H
#define BROKERAPP_CANDLECHART_H

#include "../Widgets/Widget.h"
#include "../Tickables/Tickable.h"
#include <implot.h>
#include <implot_internal.h>
#include "../Helpers/PlotHelper.h"

#include "../Widgets/Indicators.h"
#include "../Tickables/Indicator.h"

class ImPlotTime;

class CandleChart : public Widget, public Tickable{
public:
    CandleChart(Editor* editor, Ticker* ticker);
    void updateVisible(float dt) override;
    void showIndicators(bool show);
protected:
private:
    void render(float dt);
    void plotIndicators();

    char _t1_str[32];
    char _t2_str[32];
    ImPlotTime _t1;
    ImPlotTime _t2;
    std::unique_ptr<Indicators> _indicatorsView{nullptr};

    bool _showIndicators = true;
    bool _initTime = false;

    std::vector<std::unique_ptr<Indicator>> _indicators;


};




#endif //BROKERAPP_CANDLECHART_H
