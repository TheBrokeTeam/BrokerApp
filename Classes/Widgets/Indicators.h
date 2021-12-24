//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_INDICATORS_H
#define BROKERAPP_INDICATORS_H

#include "Widget.h"
#include <implot.h>
#include <implot_internal.h>
#include <vector>
#include "../Helpers/PlotHelper.h"

class Indicators : public Widget {
public:
    static inline const char* CANDLE_INDICATORS = "CANDLE_INDICATOR";
    static inline const char* VOLUME_INDICATORS = "VOLUME_INDICATOR";

    struct MyDndItem {
        int              Idx;
        int              Plt;
        ImAxis           Yax;
        char             Label[16];
        ImVector<ImVec2> Data;
        ImVec4           Color;
        MyDndItem()        {
            static int i = 0;
            Idx = i++;
            Plt = 0;
            Yax = ImAxis_Y1;
            sprintf(Label, "%02d Hz", Idx+1);
            Color = PlotHelper::RandomColor();
            Data.reserve(1001);
            for (int k = 0; k < 1001; ++k) {
                float t = k * 1.0f / 999;
                Data.push_back(ImVec2(t, 0.5f + 0.5f * sinf(2*3.14f*t*(Idx+1))));
            }
        }
        void Reset() { Plt = 0; Yax = ImAxis_Y1; }
    };

    Indicators(Editor* editor);
    void updateVisible(float dt) override;
    std::vector<MyDndItem>& getIndicators();

private:
        void drawView();
        const int _numberOfItems = 3;
        std::vector<MyDndItem>  _dragAndDropItems;
};


#endif //BROKERAPP_INDICATORS_H
