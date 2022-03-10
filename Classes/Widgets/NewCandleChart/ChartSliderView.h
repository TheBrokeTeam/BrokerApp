//
// Created by Luiz Veloso on 05/03/22.
//

#ifndef BROKERAPP_CHARTSLIDERVIEW_H
#define BROKERAPP_CHARTSLIDERVIEW_H


#include "../Widget.h"

class ChartSliderDelegate {
public:
    virtual void sliderDidScroll(float value) = 0;
};

class ChartSliderView: public Widget {
public:

    void setDelegate(ChartSliderDelegate *delegate);
    void setPositionValue(float positionValue);

    explicit ChartSliderView(Context* context);
    void updateVisible(float dt) override;
    void onPushStyleVar() override;
    void render();
private:
    ChartSliderDelegate *_delegate{nullptr};
    float _positionValue = 1;
};


#endif //BROKERAPP_CHARTSLIDERVIEW_H
