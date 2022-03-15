//
// Created by Luiz Veloso on 05/03/22.
//

#ifndef BROKERAPP_NEWCHARTVIEW_H
#define BROKERAPP_NEWCHARTVIEW_H


#include "../Widget.h"
#include "ChartRenderer.h"
#include "ChartSliderView.h"

class NewChartView: public Widget, ChartSliderDelegate, ChartRendererDelegate {
public:
    explicit NewChartView(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;

    void addChart(std::shared_ptr<ChartRenderer> chartRenderer);

protected:
    void sliderDidScroll(float value) override;
    void chartDidScroll(int lastVisibleIndex) override;

private:
    std::shared_ptr<ChartRenderer> _chart{nullptr};
    std::shared_ptr<ChartSliderView> _slider{nullptr};

    void addSlider();

};


#endif //BROKERAPP_NEWCHARTVIEW_H
