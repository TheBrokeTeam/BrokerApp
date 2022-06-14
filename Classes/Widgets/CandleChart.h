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
#include "SliderPosition.h"

class ImPlotTime;
class BackTestingContext;

class CandleChart : public Widget{
public:
    CandleChart(Context* context, Ticker* ticker);
    void updateVisible(float dt) override;

    SliderPosition* getSlider(){
        return _slider.get();
    }

    IndicatorsView* getIndicatorsView(){
        return _indicatorsView.get();
    }

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
    BackTestingContext* _context{nullptr};
    std::unique_ptr<IndicatorsView> _indicatorsView{nullptr};
    std::unique_ptr<SliderPosition> _slider{nullptr};
    bool _forceChangeMax = false;
    double _movedMin, _movedMax = 0;

};




#endif //BROKERAPP_CANDLECHART_H
