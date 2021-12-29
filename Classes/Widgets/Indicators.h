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
#include "../Tickables/Indicator.h"

class Indicators : public Widget{
public:
    typedef std::function<void(void)> TrashClickCallback;

    static inline const char* CANDLE_INDICATORS_DRAG_ID = "CANDLE_INDICATOR";
    static inline const char* VOLUME_INDICATORS_DRAG_ID = "VOLUME_INDICATOR";

    enum class CandleIndicatorsTypes{
        SMA,
        EMA,
        WMA,
        BOLL,
        VWAP,
        AVL,
        TRIX,
        SAR
    };

    struct DragAndDropIndicatorItem {
            CandleIndicatorsTypes type;
            std::string      label{""};
            DragAndDropIndicatorItem(CandleIndicatorsTypes type): type(type){
                static std::string names[8]{"SMA","EMA","WMA","BOLL","VWAP","AVL","TRIX","SAR"};
                label = names[int(type)];
        }
    };

    Indicators(Editor* editor);
    void updateVisible(float dt) override;
    std::vector<DragAndDropIndicatorItem>& getIndicators();

    void setTrashCallback(TrashClickCallback callback);

private:
    TrashClickCallback _trashCallback;
    void drawView();
    const int _numberOfItems = 8;
    std::vector<DragAndDropIndicatorItem>  _dragAndDropItems;
};


#endif //BROKERAPP_INDICATORS_H
