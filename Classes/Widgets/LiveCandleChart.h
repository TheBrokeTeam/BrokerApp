//
// Created by Arthur Abel Motelevicz on 06/02/22.
//

#ifndef BROKERAPP_LIVELiveCandleChart_H
#define BROKERAPP_LIVELiveCandleChart_H

#include "Widget.h"
#include "../Tickables/Tickable.h"
#include <implot.h>
#include <implot_internal.h>
#include "../Helpers/PlotHelper.h"

#include "IndicatorsView.h"
#include "../Tickables/Indicators/Indicator.h"

class ImPlotTime;

class LiveCandleChart : public Widget{
public:
    LiveCandleChart(Context* context, Ticker* ticker);
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

    int _lastIdxX = 0;

    float _positionerValue = 1.0f;
};



#endif //BROKERAPP_LIVELiveCandleChart_H
