//
// Created by Arthur Abel Motelevicz on 13/06/22.
//

#ifndef BROKERAPP_SLIDERPOSITION_H
#define BROKERAPP_SLIDERPOSITION_H



#include "Widget.h"

class BackTestingContext;

class SliderPosition : public Widget {
public:
    typedef std::function<void(float)> ChangeCallback;
    explicit SliderPosition(Context* context);
    void updateAlways(float dt) override;
    int getWindowFlags() override;
    void onPushStyleVar() override;

    void setChangeCallback(ChangeCallback c);
    static float GetPadding() { return 2.0f; }
    float getPercent();
    void setPercent(float p);


private:
    float _currentPercent= 1.0f;
    ChangeCallback _changeCallback{nullptr};
    BackTestingContext* _context{nullptr};
    float _movedMin, _movedMax = 0;
    bool _forceChangeMax =  true;
};

#endif //BROKERAPP_SLIDERPOSITION_H
