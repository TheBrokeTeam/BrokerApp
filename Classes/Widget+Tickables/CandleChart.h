//
// Created by Arthur Abel Motelevicz on 23/12/21.
//

#ifndef BROKERAPP_CANDLECHART_H
#define BROKERAPP_CANDLECHART_H

#include "../Widgets/Widget.h"
#include "../Tickables/Tickable.h"
#include <implot.h>
#include <implot_internal.h>

//#include "../Tickables/Indicators/Indicator.h"
//#include "../Tickables/Strategies/Strategy.h"
//#include "../Strategies/TestStrategy.h"

class ImPlotTime;

class CandleChart : public Widget, public Tickable{
public:
    CandleChart(Editor* editor, Ticker* ticker);
//    void addIndicator(const ui_event::AddIndicatorCLicked& event);

    void updateVisible(float dt) override;
//    void reset() override;

//    void setSpeed(const ui_event::SliderChanged &event);
//    void setData(const data_event::DataLoaded& event);
//    void playSimulation(const ui_event::PlaySimulationClicked &event);
//

protected:
//    void plotIndicators();
private:
    void render(float dt);

    //    std::vector<std::unique_ptr<Indicator>> _indicators;
//    std::unique_ptr<TestStrategy> _strategy{nullptr};
    char _t1_str[32];
    char _t2_str[32];
    ImPlotTime _t1;
    ImPlotTime _t2;

    bool _initTime = false;

};




#endif //BROKERAPP_CANDLECHART_H
