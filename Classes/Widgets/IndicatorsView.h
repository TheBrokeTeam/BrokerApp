//
// Created by Arthur Abel Motelevicz on 24/12/21.
//

#ifndef BROKERAPP_INDICATORSVIEW_H
#define BROKERAPP_INDICATORSVIEW_H

#include "Widget.h"
#include <implot.h>
#include <implot_internal.h>
#include <vector>
#include "../Helpers/PlotHelper.h"
#include "../Tickables/Indicators/Indicator.h"

class IndicatorsView : public Widget{
public:
    typedef std::function<void(void)> TrashClickCallback;

    static inline const char* CANDLE_INDICATORS_DRAG_ID = "CANDLE_INDICATOR";
    static inline const char* CANDLE_INDICATORS_DRAG_ID_REMOVING = "CANDLE_INDICATOR_REMOVING";
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

    enum class Nodes{
        ADD,
        MULTIPLY,
        SMA,
        CROSS,
        RESULT
    };

    struct DragAndDropIndicatorItem {
            CandleIndicatorsTypes type;
            std::string      label{""};
            DragAndDropIndicatorItem(CandleIndicatorsTypes type): type(type){
                static std::string names[8]{"SMA","EMA","WMA","BOLL","VWAP","AVL","TRIX","SAR"};
                label = names[int(type)];
        }
    };

    IndicatorsView(Context* context);
    void updateVisible(float dt) override;
    std::vector<DragAndDropIndicatorItem>& getIndicators();
    void onPushStyleVar() override;
    void setTrashCallback(TrashClickCallback callback);

private:
    TrashClickCallback _trashCallback;
    void drawView();
    const int _numberOfItems = 8;
    std::vector<DragAndDropIndicatorItem>  _dragAndDropItems;
};


#endif //BROKERAPP_INDICATORSVIEW_H
