//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CANDLECHART_H
#define BROKERAPP_CANDLECHART_H

#include "Widget.h"
#include "../Tickables/Tickable.h"
#include <implot.h>
#include <implot_internal.h>
#include "../Helpers/PlotHelper.h"

#include "IndicatorsView.h"
#include "../Tickables/Indicators/Indicator.h"

class ImPlotTime;

class CandleChart : public Widget{
public:
    CandleChart(Context* context, Ticker* ticker);
    void updateVisible(float dt) override;

protected:
private:
    void render(float dt);

    char _t1_str[32];
    char _t2_str[32];
    ImPlotTime _t1;
    ImPlotTime _t2;

    Ticker* _ticker;
    int _maxSubplots = 10;
    std::vector<float> calculateRatios();

    int _maxBarsToRender = 1000;
    int _lastIdxX = 0;
    int _lastMaxTime = 0;
    int _lastMinTime = 0;

    double _zoomOutMax;


};




#endif //BROKERAPP_CANDLECHART_H
